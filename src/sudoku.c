// name: António Dinis Myroshnyk
// description: Contains functions related to the Sudoku game

#include "../include/sudoku.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int is_valid(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int num) {
    for(int x = 0; x <= GRID_SIZE - 1; x++)
        if(grid[row][x] == num || grid[x][col] == num) return 0;
    int startRow = row - row % 2, startCol = col - col % 2;
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            if(grid[i + startRow][j + startCol] == num) return 0;
    return 1;
}

int solve_sudoku(int grid[GRID_SIZE][GRID_SIZE], int row, int col) {
    if(row == GRID_SIZE - 1 && col == GRID_SIZE) return 1;
    if(col == GRID_SIZE) row++, col = 0;
    if(grid[row][col] > 0) return solve_sudoku(grid, row, col + 1);
    for(int num = 1; num <= GRID_SIZE; num++) {
        if(is_valid(grid, row, col, num)) {
            grid[row][col] = num;
            if(solve_sudoku(grid, row, col + 1)) return 1;
        }
        grid[row][col] = 0;
    }
    return 0;
}

int check_cell(int grid[GRID_SIZE][GRID_SIZE], int row, int col) {
    if(grid[row][col] != 0) {
        int num = grid[row][col];
        grid[row][col] = 0;
        if(!is_valid(grid, row, col, num)) return 0;
        grid[row][col] = num;
    }
    return 1;
}

int is_initial_grid_valid(int grid[GRID_SIZE][GRID_SIZE]) {
    for(int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
            if(!check_cell(grid, i, j)) return 0;
        }
    }
    return 1;
}

int select_random_problem(FileData *data, int *prev_index) {
    int index;
    time_t t;
    srand((unsigned) time(&t));
    do index = rand() % data->problem_count;
    while(index == *prev_index && data->problem_count > 1);
    *prev_index = index;
    return index;
}