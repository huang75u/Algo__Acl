#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../include/dp_algorithm.h"

// Utility function to calculate the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to calculate the sum of tasks in a subset
int subset_sum(int tasks[], int subset, int N) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        if (subset & (1 << i)) { // Check if task i is in the subset
            sum += tasks[i];
        }
    }
    return sum;
}

// Dynamic programming scheduling algorithm
void DP(int tasks[], int N, int m) {
    int total_subsets = 1 << N; // Total number of subsets

    // Allocate memory for dp table
    int dp[total_subsets][m + 1];

    // Initialize dp table
    for (int i = 0; i < total_subsets; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = INT_MAX; // Set all values to infinity
        }
    }

    // Base cases
    for (int i = 0; i < total_subsets; i++) {
        dp[i][1] = subset_sum(tasks, i, N); // One machine handles all tasks in subset i
    }
    dp[0][1] = 0; // Empty set has no load

    // Fill the dp table
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
