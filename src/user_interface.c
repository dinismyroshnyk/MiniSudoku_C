// name: António Dinis Myroshnyk
// description: Contains the functions that handle the user interface

#include "../include/user_interface.h"

# include <stdio.h>
# include <string.h>

int main_menu(int allowed_attempts) {
    char input[4];
    int choice, max_choice = 5;
    if(allowed_attempts < 1) {
        printf("Too many invalid choices. ");
        return max_choice;
    }
    main_menu_interface(allowed_attempts);
    fgets(input, sizeof(input), stdin);
    choice = validate_choice(input, max_choice);
    if(choice == 0) return main_menu(--allowed_attempts);
    return choice;
}

void main_menu_interface(int allowed_attempts) {
    clear_screen();
    printf("Welcome to Sudoku!\n");
    printf("Please choose one of the following options:\n");
    printf("1. Play Sudoku\n");
    printf("2. Add new problem\n");
    printf("3. Rename problem\n");
    printf("4. View statistics\n");
    printf("5. Exit\n");
    if(allowed_attempts == 1) printf("Your choice (last attempt): ");
    else if (allowed_attempts < 5) printf("Your choice (%d): ", allowed_attempts);
    else printf("Your choice: ");
}

int validate_choice(char *input, int max_value) {
    int integer;
    char newline;
    if(sscanf(input, "%d%c", &integer, &newline) != 2 || newline != '\n') {
        printf("Invalid choice. Please enter a number.\n");
        clear_input_buffer(input);
        return 0;
    }
    if (integer < 1 || integer > max_value) {
        printf("Invalid choice. Please enter a number between 1 and %d.\n", max_value);
        clear_input_buffer(input);
        return 0;
    }
    return integer;
}

void clear_input_buffer(char *input) {
    if(!strchr(input, '\n')) while(fgetc(stdin) != '\n');
}

void clear_screen() {
    printf("\033[H\033[J");
}