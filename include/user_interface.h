// name: António Dinis Myroshnyk
// description: Header file for user interface

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

int main_menu(int allowed_attempts); // DONE
void main_menu_interface(int allowed_attempts); // DONE

void display_sudoku_grid();
void get_grid_position(int *row, int *column);

int validate_user_input(char *input, int max_value); // DONE
void clear_input_buffer(char *input); // DONE
void clear_screen(); // DONE

#endif