#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../include/fptas_algorithm.h"

// Utility function to calculate the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Utility function to calculate the sum of tasks in a subset
int subset_sum(int tasks[], int subset, int N) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        if (subset & (1 << i)) { // Check if task i is in the subset
            sum += tasks[i];
        }
    }
    return sum;
}

// FPTAS scheduling algorithm
void FPTAS(int tasks[], int N, int m, double epsilon) {
    // Find maximum task time
    int p_max = 0;
    for (int i = 0; i < N; i++) {
        if (tasks[i] > p_max) {
            p_max = tasks[i];
        }
    }

    // Calculate recommended maximum epsilon
    double epsilon_max = (double)N / p_max;
    printf("Recommended maximum epsilon: %.4f\n", epsilon_max);
    if (epsilon > epsilon_max) {
        printf("The provided approximation parameter (epsilon) is too large.\n");
        printf("Please choose epsilon less than or equal to %.4f.\n", epsilon_max);
        return;
    }

    // Calculate scaling factor
    double K = (epsilon * p_max) / N; // Adjusted scaling factor
    printf("With epsilon = %.4f, the scaling factor K will be %.4f.\n", epsilon, K);

    // Scale task times
    int scaled_tasks[N];
    for (int i = 0; i < N; i++) {
        scaled_tasks[i] = (int)(tasks[i] / K);
        if (scaled_tasks[i] < 1) { // Ensure scaled time is at least 1
            scaled_tasks[i] = 1;
        }
    }

    // Debug: Print scaled tasks
    printf("Scaled tasks: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", scaled_tasks[i]);
    }
    printf("\n");

    // Total number of subsets
    int total_subsets = 1 << N;

    // Allocate memory for dp arrays (state compression)
    int dp_prev[total_subsets]; // Previous layer
    int dp_curr[total_subsets]; // Current layer

    // Initialize dp_prev for one machine
    for (int S = 0; S < total_subsets; S++) {
        dp_prev[S] = subset_sum(scaled_tasks, S, N);
    }
    dp_prev[0] = 0; // Empty set has no load

    // Fill the dp table using state compression
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
        // Update dp_prev for the next layer
        for (int S = 0; S < total_subsets; S++) {
            dp_prev[S] = dp_curr[S];
        }
    }

    // Result is the optimal value for the full set with m machines
    int scaled_Cmax = dp_prev[total_subsets - 1];

    // Rescale the result back to original time
    double Cmax = scaled_Cmax * K;
    printf("FPTAS scheduling completed. Approximate Cmax: %.2f\n", Cmax);
}
