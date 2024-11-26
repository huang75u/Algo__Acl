#include "input_module.h"

// Global variable definitions
int tasks[MAX_TASKS];
int compatibility[MAX_TASKS][MAX_TASKS];
int machines[MAX_MACHINES];

// Read input from the user
void read_input(int *N, int *m) {
    printf("Please enter the number of tasks (N) and machines (m) (max %d and %d respectively): ", MAX_TASKS, MAX_MACHINES);
    scanf("%d %d", N, m);
    
    if (*N > MAX_TASKS || *N <= 0) {
        printf("Error: The number of tasks must be between 1 and %d.\n", MAX_TASKS);
        exit(1);
    }
    if (*m > MAX_MACHINES || *m <= 0) {
        printf("Error: The number of machines must be between 1 and %d.\n", MAX_MACHINES);
        exit(1);
    }
    
    printf("Enter the processing time for each task (separated by spaces, total %d tasks):\n", *N);
    for (int i = 0; i < *N; i++) {
        scanf("%d", &tasks[i]);
    }
    
    printf("Do you want to input a compatibility matrix for the tasks? (1 for yes, 0 for no): ");
    int need_matrix;
    scanf("%d", &need_matrix);
    
    if (need_matrix) {
        printf("Enter a %d x %d binary compatibility matrix (row by row, separated by spaces):\n", *N, *N);
        for (int i = 0; i < *N; i++) {
            for (int j = 0; j < *N; j++) {
                scanf("%d", &compatibility[i][j]);
                if (compatibility[i][j] != 0 && compatibility[i][j] != 1) {
                    printf("Error: The elements of the compatibility matrix must be 0 or 1.\n");
                    exit(1);
                }
            }
        }
    }
    printf("Input completed!\n");
}

// Generate random tasks
void generate_random_tasks(int *N, int *m, int max_time) {
    printf("Generating random tasks...\n");
    srand(time(NULL)); // Initialize random seed
    
    *N = rand() % (MAX_TASKS - 1) + 1; // Random number of tasks (between 1 and MAX_TASKS)
    *m = rand() % (MAX_MACHINES - 1) + 1; // Random number of machines (between 1 and MAX_MACHINES)
    
    for (int i = 0; i < *N; i++) {
        tasks[i] = rand() % max_time + 1; // Processing time between 1 and max_time
    }
    
    // Generate random compatibility matrix
    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < *N; j++) {
            if (i == j) {
                compatibility[i][j] = 0; // Diagonal is 0 (compatible with itself)
            } else {
                compatibility[i][j] = rand() % 2; // Generate 0 or 1
            }
        }
    }
    
    printf("Random tasks generated!\n");
    printf("Number of tasks: %d, Number of machines: %d\n", *N, *m);
    printf("Task processing times: ");
    for (int i = 0; i < *N; i++) {
        printf("%d ", tasks[i]);
    }
    printf("\n");
    
    printf("Compatibility matrix:\n");
    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < *N; j++) {
            printf("%d ", compatibility[i][j]);
        }
        printf("\n");
    }
}
