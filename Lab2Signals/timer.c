#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

// Flag updated when the SIGALRM is handled
volatile sig_atomic_t flag = 0;
// Variable to track start time of the program
time_t start_time;

// Signal handler function for SIGALRM
void handle_alarm(int signum) {
    printf("Hello World!\n");
    flag = 1;  // Set flag when signal is received
}

// Signal handler function for SIGINT (Ctrl+C)
void handle_sigint(int signum) {
    // Calculate and print total elapsed time when SIGINT is caught
    time_t end_time;
    time(&end_time);
    printf("\nTotal system time: %ld seconds\n", end_time - start_time);
    exit(0);  // Exit the program after printing time
}

int main(int argc, char *argv[]) {
    // Record the start time of the program
    time(&start_time);

    // Register the handler for SIGALRM (triggered by alarm)
    signal(SIGALRM, handle_alarm);

    // Register the handler for SIGINT (triggered by Ctrl+C)
    signal(SIGINT, handle_sigint);

    while (1) {
        // Set an alarm to trigger SIGALRM in 1 second
        alarm(1);
        flag = 0;  // Reset the flag

        // Busy wait (spin) until the SIGALRM is caught and flag is set
        while (!flag);
    }

    return 0;  // This will never be reached due to infinite loop
}
