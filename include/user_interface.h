// name: António Dinis Myroshnyk
// description: Header file for user interface

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

int main_menu(int allowed_attempts);
void main_menu_text(int allowed_attempts);
int validate_choice(char *input, int max_value);
void clear_input_buffer(char *input);
void clear_screen();

#endif