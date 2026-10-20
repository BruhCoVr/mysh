#ifndef SIGNALS_H
#define SIGNALS_H

/**
 * @brief Overwrites default behaviour for certain signals such as SIGINT or SIGTERM
 * so they do not kill the main foreground shell process.
 */
void setup_signals(void);

#endif