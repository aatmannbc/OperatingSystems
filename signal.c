/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Flag that gets updated when the signal is handled
volatile sig_atomic_t flag = 0;

// Signal handler function for SIGALRM
void handler(int signum) {
    printf("Hello World!\n");
    flag = 1;  // Set the flag when signal is caught
}

int main(int argc, char *argv[]) {
    // Register the handler function to handle SIGALRM signals
    signal(SIGALRM, handler);

    while (1) {
        // Schedule an alarm to go off in 5 seconds
        alarm(5);
        flag = 0;  // Reset the flag before waiting

        // Busy wait (spin) until the signal is delivered and flag is set
        while (!flag);

        // Once the flag is set, print this message
        printf("Turing was right!\n");
    }

    return 0;  // This will never be reached due to infinite loop
}
