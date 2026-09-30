<h1 align="center" style="bold">Testing Standard</h1>
This document will outline our projects' testing standard.\
**Contents:**
- [Testing Standard](#testing-standard)
  - [Where Tests "Live"](#where-tests-live)
  - [Test Naming Convention](#test-naming-convention)
  - [What Requires a Unit Test?](#what-requires-a-unit-test)
  - [Generating the Test Program](#generating-the-test-program)
  - [Expectations Before Merging PRs](#expectations-before-merging-prs)
  - [How End-To-End Testing Differs from Unit Testing](#how-end-to-end-testing-differs-from-unit-testing)
## Where Tests "Live"
Unit tests live in the `/tests/` directory in the project **root**.
This is where every test is contained whether it be a **unit test** or **end-to-end** test file.
## Test Naming Convention
For **modules**: `test_[module name].c`
> i.e. for `input.c` the name would be `test_input.c`

Within **module files** (the `test_[module name].c` files): `void test_[function name]_[type of test(optional)](void)`
> i.e. for testing an empty line in the `readline()` function in `input.c` the function name could be as follows below:
```C
void test_readline_empty_line(void) {/* Code goes here */}
```

## What Requires a Unit Test?
Any modules (i.e. files) that have their own functionality. The list of modules that do not require testing is shorter than the list that do. For example, the `constants.c` file does not need to be tested as it does not have any functionality besides defining constants that are used throughout the program.

Any module should have **all** functions tested **unless** the function is a forwarding/wrapper function (i.e. only calls other functions). Then, it is acceptable to only test the functions that are called.\
A notable example of this are functions such as our overloaded `print()` function which has `print_int()`, `print_str()`, etc. We only need to test `print()` with `int`, `str`, and so forth inputs rather than testing `print_int()` and `print_str()` individually.

## Generating the Test Program
If program modules have **not** been compiled (i.e. `/bin` is empty), run `make all`. The main program (`mysh`) as well as a program called `test_mysh` will be created.\
If updated program modules **have** been compiled (i.e. `/bin` is full), run `make test`. The test program (`test_mysh`) will be created.
Continue running `make test` whenever changes are made to the test modules to see if your most recently written tests pass.

## Expectations Before Merging PRs
It is expected that **all** tests pass before merging the PR into `origin/main`. This is done to ensure we do not end up with errors and *known* bugs when attempting to compile a current, running, working version of the entire program.\
It is acceptable to make a PR and explicitly state the tests are not passing before creating a sub-branch from the test branch to make fixes to the module(s) that are not passing their tests.

It is also expected for all code to be up to the agreed upon code standard, which ideally is done when the PR is opened. If the code is updated in any way after tests had been created, it is necessary to re-run the tests to ensure they still pass. Static analysis is recommended to determine if behaviour may have changed even if tests are still passing.

## How End-To-End Testing Differs from Unit Testing
**End-to-end** testing refers to running a current compiled version of the entire program with multiple different inputs to ensure it is behaving in the expected way (i.e. running commands as expected, erroring when expected with proper handling, etc...).\
**Unit** testing refers to testing individual modules and their functions. So rather than compiling the program, you create a test file (as outlined above) and test each function in the module using the testing library in `/tlib/`. Unit testing will display a "pretty" print to the console of the current function being tested as well as whether or not it passed. If a test fails, the line it failed on will be printed along with the expected vs. actual values. 