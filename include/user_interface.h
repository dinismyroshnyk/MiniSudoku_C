// name: António Dinis Myroshnyk
// description: Header file for user interface

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <file_operations.h>

int main_menu(int allowed_attempts);
void main_menu_interface(int allowed_attempts);

int validate_user_input(char *input, int max_value);
void clear_input_buffer(char *input);
void clear_screen();

void get_unique_problem_name(FileData *data);

#endif