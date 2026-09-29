<h1 align="center" style="bold">Programming Standard</h1>
This document will outline our projects' programming standard.\
**Contents:**
- [Programming Standard](#programming-standard)
  - [No Standard Library Usage](#no-standard-library-usage)
  - [Error Handling](#error-handling)
  - [Named Constants over Magic Numbers](#named-constants-over-magic-numbers)
  - [Named Structures with Methods](#named-structures-with-methods)
  - [File Layout](#file-layout)

## No Standard Library Usage
The main program (`mysh`) does not use the C standard library. Anything that libc would normally provide (memory allocation, string manipulation, formatted output, process control) must go through the system call wrapper headers (`<unistd.h>`, `<sys/wait.h>`, `<sys/syscall.h>`, etc.) or through our own thin wrappers around them in `lib.c`, `heap.c`, `output.c`, and `input.c`. Functions from `<stdio.h>`, `<stdlib.h>`, and `<string.h>` (`printf`, `malloc`, `strlen`, `strcpy`, `atoi`, libc's `exit`, ...) are not permitted.

Memory is never allocated with `malloc`/`free`. Instead, `alloc()` and `free_all()` in `heap.c` manage a fixed-size custom heap (`HEAP_SIZE`).
```C
char *input_buffer = alloc(MAX_BUFFER_SIZE);
```

Output never goes through `printf`. It goes through `print()`/`println()` in `output.c`, which are thin wrappers over the `write()` system call.

String handling uses our own `lib.c` utilities (`str_len`, `str_cpy`, `str_eq`, `itoa`, ...) instead of their libc equivalents (`strlen`, `strcpy`, `strcmp`, `itoa`). Even `exit()` is redefined in `lib.c` as a direct wrapper around the `SYS_exit_group` syscall rather than the libc version, which does extra bookkeeping (flushing buffers, running `atexit` handlers) that a freestanding program does not need or want.
```C
void exit(int status) {
    status = status & 255;
    syscall(SYS_exit_group, status);
}
```
A raw POSIX syscall wrapper such as `_exit()` is still acceptable for terminating a forked child immediately, since it skips that bookkeeping entirely rather than performing it.

Test code in `tests/` and `tlib/` is exempt, since it is not shipped as part of the shell. Even there, prefer a function that already exists in `lib.c` over reaching for a libc equivalent.

## Error Handling
System calls signal failure by returning `ERROR` (`-1`) and setting `errno`. Two rules keep this consistent across the codebase:

**1. Check return values against the status constants**, not raw literals. `constants.h` defines `SUCCESS`, `ERROR`, `EXIT`, `TRUE`, and `FALSE` for exactly this purpose, and every function that can fail should return one of them.
```C
if (get_absolute_path(command->argv[0], absolute_path) == ERROR) {
    print("Command not found: ");
    handle_error_with_memory_cleanup(command->argv[0]);
}
```

**2. Route every failure through a handler function** instead of printing or cleaning up inline at the call site. `handle_error(msg)` in `lib.c` prints `msg` (when non-empty) and returns `ERROR`; `handle_error_with_memory_cleanup(msg)` does the same after first calling `free_all()`, for use whenever heap allocations are still outstanding.
```C
int get_command(struct Command *command, int fd) {
    ...
    if (bytes_read == ERROR) {
        return handle_error_with_memory_cleanup("Error occurred while prompting input");
    }
    ...
}
```
A caller should never need to know *how* a failure is reported (message, cleanup, or eventually `exit()`) - only that calling the handler is enough.

When a syscall fails, `errno` is the only source of *why* it failed, and the handler is the one place that should read it. Reaching into `errno` at scattered call sites, or leaving it unread as in the example below, is not acceptable:
```C
// this sets errno, we have to handle it properly somehow
int status = execve(absolute_path, command->argv, environ);
```
New error paths should translate `errno` into a message (or a distinct status) inside the handler function, so every call site keeps reporting failures the same way instead of inventing its own.

## Named Constants over Magic Numbers
Any literal that is reused across files, or whose meaning is not obvious from context, must be a compile-time constant declared with `#define` in `constants.h`, named in `UPPER_SNAKE_CASE` per the [Programming Style Guide](Programming%20Style%20Guide.md#naming-convention).
```C
#define MAX_BUFFER_SIZE 256
#define MAX_ARGS 128
#define STDIN_FD 0
#define STDOUT_FD 1
```
Prefer `if (status == ERROR)` over `if (status == -1)`, and size buffers and arrays off a named constant (`char *argv[MAX_ARGS+1]`) rather than a bare number, so that changing a limit means changing one `#define` instead of hunting through every file that used the literal.

A value that is only ever used once, inside a single function, and whose meaning is already clear from the surrounding code (e.g. a loop step of `1`) does not need its own constant. Anything that appears in more than one file, sizes a buffer, or represents a fixed limit of the shell belongs in `constants.h`.

## Named Structures with Methods
Data that is passed around the shell as a unit - the currently parsed command, the shell's environment - is modeled as a named struct in its own header, declared in `PascalCase` per the style guide, with the functions that operate on it ("methods") declared alongside it in the same header. Code elsewhere should call those functions rather than reaching into the struct's fields directly.

`struct Command` (`jobs.h`) groups a command's `argv`/`argc`, and `commands.h` declares `get_command()`, `run_command()`, and `is_command_exit()` as the functions that operate on it:
```C
struct Command {
  char *argv[MAX_ARGS+1];
  unsigned int argc;
};
```
```C
int run_command(struct Command *command);
int is_command_exit(struct Command command);
```

`struct Env` (`env.h`) groups the shell's environment fields behind a single global instance (`env`), with accessor methods (`get_user()`, `get_home()`, `get_path()`, `get_pwd()`) and an `initialize_env()` that populates it, instead of scattering direct environment lookups throughout the codebase.

When introducing a new structure that is reused across modules, follow the same shape: the struct lives in its own header, its methods are declared next to it, and it gets an `initialize_`/`free_` function if it owns any resources that need setup or teardown.

## File Layout
- **`include/`** - one header per module (`module_name.h`), containing that module's struct/type declarations, shared `#define` constants (`constants.h`), and the prototypes for every function other modules are allowed to call.
- **`src/`** - one implementation file per header (`module_name.c`), containing the actual logic. `main.c` stays limited to the program's entry point and orchestration; it delegates real logic to the other modules rather than implementing it inline.
- **`tests/`** - unit and end-to-end test files, named `test_[module].c`, plus `all_tests.c` which aggregates them. See [Testing Standard.md](Testing%20Standard.md) for naming and coverage expectations.
- **`tlib/`** - the standalone test library (`tlib.c`/`tlib.h`) used to run the tests. It is kept separate from both `src/` and `tests/` since it is neither shell logic nor a set of test cases.
- **`bin/`** - build output (`.o` object files) generated by the makefile. It is not committed (see `.gitignore`).
- **Project root** - project-level docs (this file, `Programming Style Guide.md`, `Testing Standard.md`, `contract.md`), the `makefile`, and the built `mysh`/`test_mysh` binaries.

A new module always gets a matching pair: a header in `include/` and an implementation file in `src/` with the same base name. A module with its own functionality also gets a `test_[module].c` in `tests/`, per the Testing Standard.
