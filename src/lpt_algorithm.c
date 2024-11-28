#include <stdio.h>
#include <stdlib.h> 
#include "../include/lpt_algorithm.h"

// Utility function: Compare two integers in descending order
int compare_desc(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

// LPT scheduling algorithm implementation
void LPT(int tasks[], int N, int m) {
    // Step 1: Sort tasks in descending order by processing time
    qsort(tasks, N, sizeof(int), compare_desc);

    // Step 2: Initialize machine loads to 0
    int machines[m];
    for (int i = 0; i < m; i++) {
        machines[i] = 0;
    }

    // Step 3: Assign tasks to machines
    for (int i = 0; i < N; i++) {
        // Find the machine with the smallest load
        int min_machine = 0;
        for (int j = 1; j < m; j++) {
            if (machines[j] < machines[min_machine]) {
                min_machine = j;
            }
        }

        // Assign task to this machine
        machines[min_machine] += tasks[i];
        printf("Task %d (time %d) assigned to machine %d (new load: %d)\n",
               i, tasks[i], min_machine + 1, machines[min_machine]);
    }

    // Step 4: Calculate maximum completion time (Cmax)
    int Cmax = machines[0];
    for (int i = 1; i < m; i++) {
        if (machines[i] > Cmax) {
            Cmax = machines[i];
        }
    }
    printf("LPT scheduling completed. Maximum completion time (Cmax): %d\n", Cmax);
}
