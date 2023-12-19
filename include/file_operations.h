// name: António Dinis Myroshnyk
// description: Header file for file operations

#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "sudoku.h"

void generate_data_file(); // DONE
void validate_data_file();
char *trim(char *str);
int count_problems();
void load_problems(SudokuProblem problems[]);

#endif