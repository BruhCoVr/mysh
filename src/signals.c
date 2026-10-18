#include <signal.h>
#include <unistd.h>
#include <lib.h>

/**
 * @brief Prints a newline when SIGINT is captured.
 */
static void handle_sigint(int sig) {
    // Compiler warned about unused param so stuck this here to consume it
    (void)sig;
    write(STDOUT_FD, "\n", 1);
}

void setup_signals(void) {
    struct sigaction act = {0};
    
    // Ignore SIGINT (CTRL+C)
    // Need a handler for this one because we want it to work in the children
    act.sa_handler = &handle_sigint;
    if(sigaction(SIGINT, &act, NULL) == ERROR) {
        // TODO: ADD PRINTERR HERE WHEN MERGED
        exit(EXIT);
    }
    
    // Ignore SIGTSTP (CTRL+Z) everywhere
    signal(SIGTSTP, SIG_IGN);
}



