#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/dp_algorithm.h"
#include "../include/fptas_algorithm.h"
#include "../include/graph_coloring.h"
#include "../include/lpt_algorithm.h"
#include "../include/input_module.h"



int main() {
    int num_tasks, num_machines; // Number of tasks and machines
    int max_time = 100;    // Maximum time for each task

    printf("Choose the task input mode: 1. Manual input  2. Random generation\n");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        // Manual input
        read_input(&num_tasks, &num_machines);
    } else if (choice == 2) {
        // Random generation
        generate_random_tasks(&num_tasks, &num_machines, max_time);
    } else {
        printf("Invalid option! Program terminated.\n");
        return 1;
    }

    // Print generated tasks
    printf("Generated tasks:\n");
    for (int i = 0; i < num_tasks; i++) {
        printf("%d ", tasks[i]);
    }
    printf("\n");

    // Test DP algorithm
    printf("\nTesting DP Algorithm:\n");
    DP(tasks, num_tasks, num_machines);

    // Test FPTAS algorithm
    printf("\nTesting FPTAS Algorithm (epsilon = 0.1):\n");
    FPTAS(tasks, num_tasks, num_machines, 0.1);

    // Test Graph Coloring algorithm (example with no incompatibility constraints)
    printf("\nTesting Graph Coloring Algorithm:\n");
    int incompatibility[MAX_TASKS][MAX_TASKS] = {0}; // No incompatibility constraints
    graph_coloring(tasks, num_tasks, incompatibility);

    // Test LPT algorithm
    printf("\nTesting LPT Algorithm:\n");
    LPT(tasks, num_tasks, num_machines);

    return 0;
}
