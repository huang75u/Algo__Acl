#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../include/fptas_algorithm.h"


static int max(int a, int b) {
    return (a > b) ? a : b;
}

static int subset_sum(int tasks[], int subset, int N) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        if (subset & (1 << i)) { 
            sum += tasks[i];
        }
    }
    return sum;
}

// FPTAS scheduling algorithm
/*功能：实现近似调度算法（Fully Polynomial-Time Approximation Scheme，简称 FPTAS）。
输入任务数组 tasks[]，总任务数 N，机器数 m，以及近似参数 epsilon。
算法输出最优的近似最大负载（Cmax），保证近似误差不超过给定范围（由 epsilon 决定）。
参数说明：
tasks[]：表示任务数组，每个任务的负载为 tasks[i]。
N：任务的总数。
m：机器的总数。
epsilon：近似误差范围，越小结果越接近最优，但计算复杂度增加。
p_max 决定了任务的最大时间，影响算法的缩放因子和计算精度。
作用：计算一个合理的最小 epsilon 值 epsilon_min。
若 epsilon < epsilon_min，则近似误差可能过小，导致算法效率下降甚至无法执行。

*/
void FPTAS(int tasks[], int N, int m, double epsilon) {
    // Find maximum task time
    int p_max = 0;
    for (int i = 0; i < N; i++) {
        if (tasks[i] > p_max) {
            p_max = tasks[i];
        }
    }

    // Calculate recommended minimum epsilon
    double epsilon_min = (double)N / p_max;
    /*作用：计算任务时间缩放因子 K，用于将任务负载值缩小，减少动态规划表的规模*/
    printf("Recommended minimum epsilon: %.4f\n", epsilon_min);
    if (epsilon < epsilon_min) {
        printf("The provided approximation parameter (epsilon) is too little.\n");
        printf("Please choose epsilon more than or equal to %.4f.\n", epsilon_min);
        return;
    }

    // Calculate scaling factor
    double K = (epsilon * p_max) / N; 
    /*作用：根据缩放因子 K，将每个任务的负载值除以 K，并取整。
    保证：每个缩放后的负载值至少为 1，避免某些任务被舍入为 0。
    结果：得到一个新的任务数组 scaled_tasks[]，负载值较小。*/
    printf("With epsilon = %.4f, the scaling factor K will be %.4f.\n", epsilon, K);

    // Scale task times
    int scaled_tasks[N];
    for (int i = 0; i < N; i++) {
        scaled_tasks[i] = (int)(tasks[i] / K);
        if (scaled_tasks[i] < 1) { // Ensure scaled time is at least 1
            scaled_tasks[i] = 1;
        }
    }

    
    printf("Scaled tasks: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", scaled_tasks[i]);
    }
    printf("\n");

    // Total number of subsets
    int total_subsets = 1 << N;

    
    int dp_prev[total_subsets]; // Previous layer
    int dp_curr[total_subsets]; // Current layer
    /*作用：
    dp_prev：保存上一层机器的 DP 状态。
    dp_curr：保存当前机器的 DP 状态。
    大小：total_subsets = 2^N，表示任务的所有子集数。*/

    // Initialize dp_prev for one machine
    for (int S = 0; S < total_subsets; S++) {
        dp_prev[S] = subset_sum(scaled_tasks, S, N);
    }
    dp_prev[0] = 0; // Empty set has no load

    
    for (int j = 2; j <= m; j++) { // Number of machines
        printf("Processing machine %d...\n", j);
        for (int S = 0; S < total_subsets; S++) { // Iterate over all subsets
            dp_curr[S] = INT_MAX;
            for (int T = S; T > 0; T = (T - 1) & S) { // Iterate over all subsets T of S
                int remaining = S & ~T; // Remaining tasks in S not in T
                int current_load = subset_sum(scaled_tasks, remaining, N);
                dp_curr[S] = (dp_curr[S] < max(dp_prev[T], current_load)) ? dp_curr[S] : max(dp_prev[T], current_load);
            }
        }
        
        for (int S = 0; S < total_subsets; S++) {
            dp_prev[S] = dp_curr[S];
            /*dp_prev[T]：表示子集 T 分配到 j-1 台机器的最优负载。
c           urrent_load：剩余任务由当前机器处理的总负载。*/
        }
    }

    // Result is the optimal value for the full set with m machines
    int scaled_Cmax = dp_prev[total_subsets - 1];

    // Rescale the result back to original time
    double Cmax = scaled_Cmax * K;
    printf("FPTAS scheduling completed. Approximate Cmax: %.2f\n", Cmax);
}
