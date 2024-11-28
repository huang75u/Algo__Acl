#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/graph_coloring.h"
#include "../include/input_module.h" // 使用输入模块提供的任务和矩阵

#define MAX_TASKS 100

// Function to find the first available color for a task
int find_available_color(int task, int num_tasks, int incompatibility[MAX_TASKS][MAX_TASKS], int colors[]) {
    int used_colors[MAX_TASKS] = {0};

    // Mark colors used by adjacent tasks
    for (int i = 0; i < num_tasks; i++) {
        if (incompatibility[task][i] == 1 && colors[i] != -1) {
            used_colors[colors[i]] = 1;
        }
    }

    // Find the first unused color
    for (int color = 0; color < MAX_TASKS; color++) {
        if (!used_colors[color]) {
            return color;
        }
    }
    return -1; // Should not happen
}

// Graph coloring algorithm
void graph_coloring(int tasks[], int num_tasks, int incompatibility[MAX_TASKS][MAX_TASKS]) {
    int colors[MAX_TASKS]; // Stores the color (machine) assigned to each task
    memset(colors, -1, sizeof(colors)); // Initialize all tasks with no color

    // Sort tasks by processing time in descending order (greedy strategy)
    int sorted_indices[MAX_TASKS];
    for (int i = 0; i < num_tasks; i++) {
        sorted_indices[i] = i;
    }
    for (int i = 0; i < num_tasks - 1; i++) {
        for (int j = i + 1; j < num_tasks; j++) {
            if (tasks[sorted_indices[i]] < tasks[sorted_indices[j]]) {
                int temp = sorted_indices[i];
                sorted_indices[i] = sorted_indices[j];
                sorted_indices[j] = temp;
            }
        }
    }

    // Assign colors to tasks
    int max_color = 0;
    for (int i = 0; i < num_tasks; i++) {
        int task = sorted_indices[i];
        int color = find_available_color(task, num_tasks, incompatibility, colors);
        colors[task] = color;
        if (color > max_color) {
            max_color = color;
        }
    }

    // Output the results
    printf("\nGraph coloring completed.\n");
    printf("Number of machines used: %d\n", max_color + 1);

    // Calculate load on each machine
    int machine_loads[MAX_TASKS] = {0};
    for (int i = 0; i < num_tasks; i++) {
        machine_loads[colors[i]] += tasks[i];
    }

    // Print task assignments and machine loads
    for (int i = 0; i <= max_color; i++) {
        printf("Machine %d: Load = %d, Tasks = ", i + 1, machine_loads[i]);
        for (int j = 0; j < num_tasks; j++) {
            if (colors[j] == i) {
                printf("%d (task %d) ", tasks[j], j);
            }
        }
        printf("\n");
    }
}
