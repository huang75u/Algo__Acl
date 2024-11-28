#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/input_module.h"

// Global variables
int tasks[MAX_TASKS];
int compatibility[MAX_TASKS][MAX_TASKS];

// Generate random tasks
void generate_random_tasks(int *N, int *m, int max_time) {
    srand(time(NULL)); // Initialize random seed

    *N = rand() % (MAX_TASKS - 1) + 1; // Randomly generate the number of tasks (1 to MAX_TASKS)
    *m = rand() % (MAX_MACHINES - 1) + 1; // Randomly generate the number of machines (1 to MAX_MACHINES)

    for (int i = 0; i < *N; i++) {
        tasks[i] = rand() % max_time + 1; // Processing time between 1 and max_time
    }

    // By default, all tasks are compatible
    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < *N; j++) {
            compatibility[i][j] = 0; // Fully compatible
        }
    }
}

// Generate random compatibility matrix
void generate_random_compatibility_matrix(int N, int matrix[MAX_TASKS][MAX_TASKS]) {
    srand(time(NULL)); // Initialize random seed
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                matrix[i][j] = 0; // A task is always compatible with itself
            } else {
                matrix[i][j] = rand() % 2; // Randomly generate 0 or 1
            }
        }
    }
}

// Input function
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
        printf("Do you want to randomly generate the compatibility matrix? (1 for yes, 0 for manual input): ");
        int random_matrix;
        scanf("%d", &random_matrix);

        if (random_matrix) {
            generate_random_compatibility_matrix(*N, compatibility);
            printf("Generated compatibility matrix:\n");
            for (int i = 0; i < *N; i++) {
                for (int j = 0; j < *N; j++) {
                    printf("%d ", compatibility[i][j]);
                }
                printf("\n");
            }
        } else {
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
    } else {
        for (int i = 0; i < *N; i++) {
            for (int j = 0; j < *N; j++) {
                compatibility[i][j] = 0; // Fully compatible
            }
        }
    }
    printf("Input completed!\n");
}
