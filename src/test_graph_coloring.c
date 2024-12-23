#include <stdio.h>
#include "../include/graph_coloring.h"
#include "../include/input_module.h"

int main() {
    int N, m;

    printf("Task graph coloring test\n");

   
    read_input(&N, &m);

    printf("\nTasks:\n");
    for (int i = 0; i < N; i++) {
        printf("Task %d: Time = %d\n", i, tasks[i]);
    }

    printf("\nCompatibility Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", compatibility[i][j]);
        }
        printf("\n");
    }

   
    graph_coloring(tasks, N, compatibility);

    return 0;
}
