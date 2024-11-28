#include <stdio.h>
#include "../include/graph_coloring.h"
#include "../include/input_module.h"

int main() {
    int N, m;

    printf("Task graph coloring test\n");

    // 使用 input_module 提供的 read_input 函数进行任务和不相容性矩阵的输入
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

    // 调用图染色算法
    graph_coloring(tasks, N, compatibility);

    return 0;
}
