// name: António Dinis Myroshnyk
// description: Header file for Sudoku functions

#ifndef SUDOKU_H
#define SUDOKU_H

#include "common.h"

int is_valid(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int num);
int solve_sudoku(int grid[GRID_SIZE][GRID_SIZE], int row, int col);
int is_initial_grid_valid(int grid[GRID_SIZE][GRID_SIZE]);
int check_cell(int grid[GRID_SIZE][GRID_SIZE], int row, int col);

int select_random_problem(FileData *data, int *prev_index);

#endif