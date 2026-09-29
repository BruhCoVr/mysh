#include "main.h"
#include <env.h>

// int argc, char **argv
int main() {
    initialize_env();

    struct Command command;
    get_command(&command, STDIN_FD);

    while (is_command_exit(command) == FALSE) {
        run_command(&command);
        get_command(&command, STDIN_FD);
    }

    return 0;
}
