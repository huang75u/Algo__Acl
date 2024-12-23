#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../include/dp_algorithm.h"


static int max(int a, int b) {
    return (a > b) ? a : b;
}

/*计算一个任务子集的总任务负载。输入参数：
tasks[]：任务数组，其中 tasks[i] 表示任务 i 的负载值。
subset：以位掩码的形式表示的任务子集。例如，subset = 5（二进制为 101），表示第 0 和第 2 个任务在子集中。
N：任务总数。
逻辑：
使用按位与操作 subset & (1 << i) 判断任务 i 是否属于该子集。
如果属于子集，则将其负载 tasks[i] 加入到总和中。
返回值：任务子集的总负载。负载就是说（一个）任务的完成所需的时间。。。
假设：

tasks = {3, 5, 8}：表示共有 3 个任务，其负载值分别为 3、5 和 8。
subset = 5（二进制为 101）：表示子集包含任务 0 和任务 2。
N = 3：任务总数。
函数执行过程：

初始化：sum = 0
遍历任务：
第 0 个任务：
(1 << 0) 结果为 0001（十进制 1）。
subset & (1 << 0) 结果为 0001 & 0101 = 0001（非零）。
任务 0 属于子集，将 tasks[0] = 3 加入 sum：sum = 0 + 3 = 3。
第 1 个任务：
(1 << 1) 结果为 0010（十进制 2）。
subset & (1 << 1) 结果为 0010 & 0101 = 0000（零）。
任务 1 不属于子集，跳过。
第 2 个任务：
(1 << 2) 结果为 0100（十进制 4）。
subset & (1 << 2) 结果为 0100 & 0101 = 0100（非零）。
任务 2 属于子集，将 tasks[2] = 8 加入 sum：sum = 3 + 8 = 11。
返回值：sum = 11。*/
static int subset_sum(int tasks[], int subset, int N) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        if (subset & (1 << i)) { // Check if task i is in the subset
            sum += tasks[i];
        }
    }
    return sum;
}
/*输入：
tasks = {3, 5, 8}（任务负载）。
N = 3（任务总数）。
m = 2（机器总数）。
状态表过程：
初始化单机时的任务负载：
dp[{1, 0, 0}][1] = 3
dp[{1, 1, 0}][1] = 8
dp[{1, 1, 1}][1] = 16
对于 j = 2（两台机器）：
子集 S = {1, 1, 1} 分配：
子集 T = {1, 0, 0}，剩余负载为 $13$，最优负载 $8$。
子集 T = {1, 1, 0}，最优负载 $8$。
结果为 $C_{\text{max}} = 8$。
remaining = S & ~T：表示从 S 中移除 T 后的剩余任务。
current_load = subset_sum(tasks, remaining, N)：计算这些剩余任务由第 j 台机器处理时的总负载。*/
// Dynamic programming scheduling algorithm
void DP(int tasks[], int N, int m) {
    int total_subsets = 1 << N; 

   
    int dp[total_subsets][m + 1];

   
    for (int i = 0; i < total_subsets; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = INT_MAX; 
    }

   
    for (int i = 0; i < total_subsets; i++) {
        dp[i][1] = subset_sum(tasks, i, N); // One machine handles all tasks in subset i
    }
    dp[0][1] = 0; // Empty set has no load
    
    for (int j = 2; j <= m; j++) { // Number of machines
        for (int S = 0; S < total_subsets; S++) { // Iterate over all subsets
            for (int T = S; T > 0; T = (T - 1) & S) { // Iterate over all subsets T of S
                int remaining = S & ~T; // Remaining tasks in S not in T
                int current_load = subset_sum(tasks, remaining, N);
                dp[S][j] = (dp[S][j] < max(dp[T][j-1], current_load)) ? dp[S][j] : max(dp[T][j-1], current_load);
            }
        }
    }

    // Result is the optimal value for the full set with m machines
    printf("Dynamic programming scheduling completed. Minimum Cmax: %d\n", dp[total_subsets - 1][m]);
}
