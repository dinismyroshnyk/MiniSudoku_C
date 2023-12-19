// name: António Dinis Myroshnyk
// description: Header file for Sudoku functions

#ifndef SUDOKU_H
#define SUDOKU_H

#define MAX_PROBLEMS 100
#define GRID_SIZE 4

typedef struct {
    char name[50];
    int times_played;
    int grid[GRID_SIZE][GRID_SIZE];
} SudokuProblem;

void play_sudoku();
void select_random_problem();
int validate_move(int row, int column, int value);

#endif