// name: António Dinis Myroshnyk
// description: File containing the constants used in the program

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>

#define MAX_RECURSION_DEPTH 5

#define FILE_BUFFER 256
#define USER_BUFFER 40
#define MIN_DATA_VALUE 0

#define MAX_PROBLEMS 100
#define GRID_SIZE 4

typedef struct {
    char name[USER_BUFFER];
    int times_played_total, times_played_session;
    int grid[GRID_SIZE][GRID_SIZE];
} SudokuProblem;

typedef struct {
    FILE *file;
    int games_played, games_won, success_rate;
    int line_number, problem_count;
    SudokuProblem problems[MAX_PROBLEMS];
} FileData;

typedef struct {
    int grid[GRID_SIZE][GRID_SIZE];
    char problem_name[USER_BUFFER];
    int possible_errors, completed;
} GameState;

typedef struct {
    FILE *file, *temp;
    FileData *data;
    int index;
} FileUpdate;

#endif