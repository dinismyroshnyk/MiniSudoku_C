// name: António Dinis Myroshnyk
// description: Header file for user interface

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "common.h"

int menu(int max_value, int is_main_menu, GameState *game);
void main_menu_interface(int allowed_attempts);

int validate_user_input(char *input, int max_value, int min_value);
void clear_input_buffer(char *input);
void clear_screen();

void get_unique_problem_name(FileData *data, int index);
void update_problem_name(FileData *data, char *problem_name, int index);
void get_sudoku_grid(FileData *data);
int get_valid_cell(int row, int col);

int get_problem_index(FileData *data);
void get_problem_name(char *problem_name, int size);

void print_sudoku_grid(int grid[GRID_SIZE][GRID_SIZE]);
void play_menu_interface(GameState *game, int allowed_attempts);
void place_number(GameState *game, FileData *data);
int get_valid_input(const char *message, int is_index);
void remove_number(int grid[GRID_SIZE][GRID_SIZE], int initial_grid[GRID_SIZE][GRID_SIZE]);
void press_any_key_message(char *message);
int check_win(int grid[GRID_SIZE][GRID_SIZE]);

#endif