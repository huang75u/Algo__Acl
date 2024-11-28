#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/input_module.h"

// 全局变量
int tasks[MAX_TASKS];
int compatibility[MAX_TASKS][MAX_TASKS];

// 随机生成兼容性矩阵
void generate_random_compatibility_matrix(int N, int matrix[MAX_TASKS][MAX_TASKS]) {
    srand(time(NULL)); // 初始化随机数种子
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                matrix[i][j] = 0; // 自己与自己兼容
            } else {
                matrix[i][j] = rand() % 2; // 随机生成 0 或 1
            }
        }
    }
}

// 输入函数，包含随机和手动两种输入方式
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
        // 如果用户选择不输入兼容性矩阵，默认所有任务之间兼容
        for (int i = 0; i < *N; i++) {
            for (int j = 0; j < *N; j++) {
                compatibility[i][j] = 0; // 所有任务都相互兼容
            }
        }
    }
    printf("Input completed!\n");
}
