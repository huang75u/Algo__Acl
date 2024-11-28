#ifndef GRAPH_COLORING_H
#define GRAPH_COLORING_H

#define MAX_TASKS 100

/**
 * @brief Implements the graph coloring algorithm to solve the task scheduling problem 
 *        with incompatibility constraints.
 * 
 * @param tasks Array of task processing times.
 * @param num_tasks Number of tasks.
 * @param incompatibility 2D array representing the incompatibility matrix, 
 *                        where incompatibility[i][j] = 1 indicates tasks i and j are incompatible.
 */
void graph_coloring(int tasks[], int num_tasks, int incompatibility[MAX_TASKS][MAX_TASKS]);

#endif // GRAPH_COLORING_H
