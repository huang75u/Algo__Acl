#include <stdio.h>
#include "../include/input_module.h"

int main() {
    int N, m; // Number of tasks and machines

    // Use the input module
    printf("Choose the task input mode: 1. Manual input  2. Random generation\n");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        read_input(&N, &m);
    } else if (choice == 2) {
        int max_time;
        printf("Please enter the maximum processing time for a task: ");
        scanf("%d", &max_time);
        generate_random_tasks(&N, &m, max_time);
    } else {
        printf("Invalid option! Program terminated.\n");
        return 1;
    }

    // Example: Display tasks and the number of machines
    printf("Number of tasks: %d, Number of machines: %d\n", N, m);
    printf("Task processing times: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", tasks[i]);
    }
    printf("\n");

    return 0;
}
