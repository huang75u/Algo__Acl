#ifndef INPUT_MODULE_H
#define INPUT_MODULE_H

#define MAX_TASKS 100
#define MAX_MACHINES 10

// Global variables
extern int tasks[MAX_TASKS];
extern int compatibility[MAX_TASKS][MAX_TASKS];

// Function declarations
void generate_random_tasks(int *N, int *m, int max_time);
void generate_random_compatibility_matrix(int N, int matrix[MAX_TASKS][MAX_TASKS]);
void read_input(int *N, int *m);

#endif
