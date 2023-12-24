// name: António Dinis Myroshnyk
// description: Contains the functions that handle the user interface

#include "../include/user_interface.h"
#include "../include/file_operations.h"

# include <stdio.h>
# include <string.h>

int main_menu(int allowed_attempts) {
    char input[4];
    int choice, max_choice = 5, min_choice = 1;
    if(allowed_attempts < 1) {
        clear_screen();
        printf("Too many invalid choices. ");
        return max_choice;
    }
    main_menu_interface(allowed_attempts);
    fgets(input, sizeof(input), stdin);
    choice = validate_user_input(input, max_choice, min_choice);
    if(choice == -1) return main_menu(--allowed_attempts);
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

int validate_user_input(char *input, int max_value, int min_value) {
    int integer;
    char newline;
    if(sscanf(input, "%d%c", &integer, &newline) != 2 || newline != '\n') {
        printf("Invalid choice. Please enter a number. ");
        clear_input_buffer(input);
        return -1;
    }
    if (integer < min_value || integer > max_value) {
        printf("Invalid choice. Please enter a number between %d and %d. ", min_value, max_value);
        clear_input_buffer(input);
        return -1;
    }
    return integer;
}

void clear_input_buffer(char *input) {
    if(!strchr(input, '\n')) while(fgetc(stdin) != '\n');
}

void clear_screen() {
    printf("\033[H\033[J");
}

void get_unique_problem_name(FileData *data, int index) {
    char problem_name[USER_BUFFER];
    while(1) {
        clear_screen();
        printf("Problem name: ");
        fgets(problem_name, sizeof(problem_name), stdin);
        clear_input_buffer(problem_name);
        if(problem_name[strlen(problem_name) - 1] == '\n') problem_name[strlen(problem_name) - 1] = '\0';
        if(validate_problem_name(data, problem_name, 0)) {
            update_problem_name(data, problem_name, index);
            break;
        }
    }
}

void update_problem_name(FileData *data, char *problem_name, int index) {
    if(index == -1) {
        strcpy(data->problems[data->problem_count].name, problem_name);
        data->problem_count++;
    } else strcpy(data->problems[index].name, problem_name);
}

void get_sudoku_grid(FileData *data) {
    int grid[GRID_SIZE][GRID_SIZE], copy[GRID_SIZE][GRID_SIZE];
    while (1) {
        printf("Enter the problem grid. ");
        for(int i = 0; i < GRID_SIZE; i++) {
            for(int j = 0; j < GRID_SIZE; j++) {
                grid[i][j] = get_valid_cell(i, j);
            }
        }
        memcpy(copy, grid, GRID_SIZE * GRID_SIZE * sizeof(int));
        if (!is_initial_grid_valid(grid) || !solve_sudoku(grid, 0, 0)) {
            printf("Invalid Sudoku puzzle. The problem is not solvable. Please try again.\n");
        } else break;
    }
    memcpy(data->problems[data->problem_count].grid, copy, GRID_SIZE * GRID_SIZE * sizeof(int));
    data->problems[data->problem_count].times_played_total = 0;
    data->problem_count++;
}

int get_valid_cell(int row, int col) {
    char input[USER_BUFFER];
    int value;
    while (1) {
        printf("(Row %d, Column %d): ", row + 1, col + 1);
        fgets(input, sizeof(input), stdin);
        value = validate_user_input(input, GRID_SIZE, MIN_DATA_VALUE);
        if (value >= MIN_DATA_VALUE && value <= GRID_SIZE) break;
    }
    return value;
}

int get_problem_index(FileData *data) {
    char problem_name[USER_BUFFER];
    while(1) {
        get_problem_name(problem_name, sizeof(problem_name));
        for(int i = 0; i < data->problem_count; i++) {
            if(strcmp(problem_name, data->problems[i].name) == 0) return i;
        }
        printf("The problem name is not in the list. Please try again.\n");
    }
}

void get_problem_name(char *problem_name, int size) {
    printf("Enter the name of the problem: ");
    fgets(problem_name, size, stdin);
    clear_input_buffer(problem_name);
    if(problem_name[strlen(problem_name) - 1] == '\n') problem_name[strlen(problem_name) - 1] = '\0';
}