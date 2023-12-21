// name: António Dinis Myroshnyk
// description: Header file for file operations

#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <stdio.h>

#include "sudoku.h"

#define FILE_BUFFER 256
#define USER_BUFFER 40
#define MIN_DATA_VALUE 0

typedef struct {
    FILE *file;
    int games_played, games_won, success_rate;
    int line_number, problem_count;
} FileData;

void generate_data_file(); // DONE
void validate_data_file();
void validate_statistics(FileData *data);
void validate_problems(FileData *data);
void validate_problem_grid(FileData *data, int grid[GRID_SIZE]);
FILE *open_file(const char *filename, const char *mode);
void check_int_range(FileData *data, int value, int max, const char *message);
void check_success_rate(FileData *data, int value, int max, const char *message);
char *read_line(FileData *data, char *buffer, int buffer_size);
void exit_error_message(FileData *data, const char *message, int print_check, int extra_values[2]);
FileData init_file_context(const char *filename);
void validate_problem_count(FileData *data);
void validate_total_games_across_problems(FileData *data, int games_played_across_problems);

int count_problems();
void load_problems(SudokuProblem problems[]);

char *trim(char *str);

#endif