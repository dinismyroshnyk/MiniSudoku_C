// name: António Dinis Myroshnyk
// description: Header file for file operations

#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <stdio.h>

#include "constants.h"
#include "sudoku.h"

typedef struct {
    FILE *file;
    int games_played, games_won, success_rate;
    int line_number, problem_count;
    SudokuProblem problems[MAX_PROBLEMS];
} FileData;

void generate_data_file(); // DONE
FileData validate_data_file();
void validate_statistics(FileData *data);
void validate_problems(FileData *data);
void validate_problem_grid(FileData *data, int grid[GRID_SIZE][GRID_SIZE]);
FILE *open_file(const char *filename, const char *mode);
void check_int_range(FileData *data, int value, int max, const char *message);
void check_success_rate(FileData *data, int value, int max, const char *message);
char *read_line(FileData *data, char *buffer, int buffer_size);
void exit_error_message(FileData *data, const char *message, int print_check, int extra_values[2]);
FileData init_file_data(const char *filename);
void validate_problem_count(FileData *data);
void validate_total_games_across_problems(FileData *data, int games_played_across_problems);
void validate_sudoku_problem(FileData *data, int grid[GRID_SIZE][GRID_SIZE]);
char *trim(char *str);
void validate_problem_name(FileData *data, char *problem_name, int exit_flag);
void add_problem_to_data(FileData *data, char *problem_name, int times_played, int grid[GRID_SIZE][GRID_SIZE]);

#endif