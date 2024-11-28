#include "../include/input_module.h"
#include "../include/dp_algorithm.h"
int main() {
    int N, m; // Number of tasks and machines

    // Choose input mode
    printf("Choose the task input mode: 1. Manual input  2. Random generation\n");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        // Manual input
        read_input(&N, &m);
    } else if (choice == 2) {
        // Random generation
        int max_time;
        printf("Please enter the maximum processing time for a task: ");
        scanf("%d", &max_time);
        generate_random_tasks(&N, &m, max_time);
    } else {
        printf("Invalid option! Program terminated.\n");
        return 1;
    }

    // Perform dynamic programming scheduling
    printf("\nStarting dynamic programming scheduling...\n");
    DP(tasks, N, m);

    return 0;
}
