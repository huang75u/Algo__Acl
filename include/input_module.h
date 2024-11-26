#ifndef INPUT_MODULE_H
#define INPUT_MODULE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constants
#define MAX_TASKS 100       // Maximum number of tasks
#define MAX_MACHINES 10     // Maximum number of machines
#define MAX_COMPATIBILITY 100 // Maximum dimension for the compatibility matrix

// Global variables (initialized in the input module)
extern int tasks[MAX_TASKS];              // Processing time of each task
extern int compatibility[MAX_TASKS][MAX_TASKS]; // Compatibility matrix
extern int machines[MAX_MACHINES];        // Current load of each machine

// Function prototypes
void read_input(int *N, int *m);                  // Read input from the user
void generate_random_tasks(int *N, int *m, int max_time); // Generate random tasks

#endif // INPUT_MODULE_H
