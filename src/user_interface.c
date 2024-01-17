// name: António Dinis Myroshnyk
// description: Contains the functions that handle the user interface

#include "../include/user_interface.h"
#include "../include/file_operations.h"
#include "../include/sudoku.h"

# include <stdio.h>
# include <string.h>

int menu(int max_value, int menu_flag, GameState *game, FileData *data) {
    static int allowed_attempts = MAX_RECURSION_DEPTH;
    char input[4];
    int choice;
    if(allowed_attempts < 1) {
        clear_screen();
        printf("Too many invalid choices. ");
        allowed_attempts = MAX_RECURSION_DEPTH;
        return max_value;
    }
    switch(menu_flag) {
        case 1:
            main_menu_interface(allowed_attempts);
            break;
        case 2:
            play_menu_interface(game, allowed_attempts);
            break;
        case 3:
            display_info_interface(data, allowed_attempts);
            break;
        default:
            press_any_key_message("You should not be seeing this message. Please report this bug.");
            break;
    }
    fgets(input, sizeof(input), stdin);
    choice = validate_user_input(input, max_value, 1);
    if(choice == -1) {
        allowed_attempts--;
        return menu(max_value, menu_flag, game, data);
    }
    allowed_attempts = MAX_RECURSION_DEPTH;
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
    else if (allowed_attempts < MAX_RECURSION_DEPTH) printf("Your choice (%d): ", allowed_attempts);
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
    if(integer < min_value || integer > max_value) {
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
        printf("New problem name: ");
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
    if(index == -1) strcpy(data->problems[data->problem_count].name, problem_name);
    else strcpy(data->problems[index].name, problem_name);
}

void get_sudoku_grid(FileData *data) {
    int grid[GRID_SIZE][GRID_SIZE], copy[GRID_SIZE][GRID_SIZE];
    while(1) {
        printf("Enter the problem grid. ");
        for(int i = 0; i < GRID_SIZE; i++) {
            for(int j = 0; j < GRID_SIZE; j++) {
                grid[i][j] = get_valid_cell(i, j);
            }
        }
        memcpy(copy, grid, GRID_SIZE * GRID_SIZE * sizeof(int));
        if(!is_initial_grid_valid(grid) || !solve_sudoku(grid, 0, 0)) {
            printf("Invalid Sudoku puzzle. The problem is not solvable. Please try again.\n");
        } else break;
    }
    add_problem_to_data(data, 0, copy);
}

int get_valid_cell(int row, int col) {
    char input[USER_BUFFER];
    int value;
    while(1) {
        printf("(Row %d, Column %d): ", row + 1, col + 1);
        fgets(input, sizeof(input), stdin);
        value = validate_user_input(input, GRID_SIZE, MIN_DATA_VALUE);
        if(value >= MIN_DATA_VALUE && value <= GRID_SIZE) break;
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

void print_sudoku_grid(int grid[GRID_SIZE][GRID_SIZE]) {
    printf("      1   2   3   4\n\n");
    for(int i = 0; i < GRID_SIZE; i++) {
        printf("    +---+---+---+---+\n");
        printf("%d   |", i + 1);
        for(int j = 0; j < GRID_SIZE; j++) {
            if(grid[i][j] == 0) printf("   |");
            else printf(" %d |", grid[i][j]);
        }
        printf("\n");
    }
    printf("    +---+---+---+---+\n");
}

void play_menu_interface(GameState *game, int allowed_attempts) {
    clear_screen();
    printf("    %s\n\n", game->problem_name);
    print_sudoku_grid(game->grid);
    printf("\nPossible errors left: %d\n", game->possible_errors);
    printf("\n1. Place number\n");
    printf("2. Remove number\n");
    printf("3. Forfeit game\n\n");
    if(allowed_attempts == 1) printf("Your choice (last attempt): ");
    else if (allowed_attempts < MAX_RECURSION_DEPTH) printf("Your choice (%d): ", allowed_attempts);
    else printf("Your choice: ");
}

void place_number(GameState *game, FileData *data) {
    int row = get_valid_input("Enter the row", 1);
    int col = get_valid_input("Enter the column", 1);
    if(game->grid[row][col] != 0) {
        press_any_key_message("The cell is already filled.");
        return;
    }
    int value = get_valid_input("Enter the value", 0);
    if(!is_valid(game->grid, row, col, value)) {
        game->possible_errors -= 1;
        game->grid[row][col] = value;
        press_any_key_message("Invalid move.");
    } else {
        game->grid[row][col] = value;
        if(check_win(game->grid)) {
            press_any_key_message("Congratulations! You have won the game.");
            game->completed = 1;
            data->games_won++;
        }
    }
    if(game->possible_errors == 0) {
        press_any_key_message("You have made too many mistakes. You have lost the game.");
    }
}

int get_valid_input(const char *message, int is_index) {
    char input[USER_BUFFER];
    int value;
    while(1) {
        printf("%s (1-%d): ", message, GRID_SIZE);
        fgets(input, sizeof(input), stdin);
        if(is_index) value = validate_user_input(input, GRID_SIZE, 1) - 1;
        else value = validate_user_input(input, GRID_SIZE, 1);
        if(value >= 0) break;
    }
    return value;
}

void remove_number(int grid[GRID_SIZE][GRID_SIZE], int initial_grid[GRID_SIZE][GRID_SIZE]) {
    int row = get_valid_input("Enter the row", GRID_SIZE);
    int col = get_valid_input("Enter the column", GRID_SIZE);
    if(initial_grid[row][col] == 0) grid[row][col] = 0;
    else if(grid[row][col] == 0) {
        printf("The cell is already empty.\n");
        printf("Press any key to continue... ");
        getchar();
    }
    else {
        printf("You cannot remove this number.\n");
        printf("Press any key to continue... ");
        getchar();
    }
}

void press_any_key_message(char *message) {
    printf("%s\n", message);
    printf("Press any key to continue... ");
    getchar();
}

int check_win(int grid[GRID_SIZE][GRID_SIZE]) {
    for(int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
            if(grid[i][j] == 0) return 0;
        }
    }
    return 1;
}

int check_problem_limit(FileData *data) {
    if(data->problem_count >= MAX_PROBLEMS) {
        press_any_key_message("You have reached the maximum number of problems. Cannot add more problems.");
        return 1;
    }
    return 0;
}

void display_problem_names(FileData *data) {
    clear_screen();
    printf("Existing problems:\n");
    for(int i = 0; i < data->problem_count; i++) {
        printf("%d. %s\n", i + 1, data->problems[i].name);
    }
}

void display_stats(FileData *data) {
    printf("Total games played: %d\n", data->games_played);
    printf("Total games won: %d\n", data->games_won);
    printf("Success rate: %.2f%%\n\n", (float)(data->success_rate) / 100);
    display_problem_names(data);
    printf("\n");
}

void display_info_interface(FileData *data, int allowed_attempts) {
    clear_screen();
    display_stats(data);
    printf("1. View problem details\n");
    printf("2. Return to main menu\n");
    if(allowed_attempts == 1) printf("Your choice (last attempt): ");
    else if (allowed_attempts < MAX_RECURSION_DEPTH) printf("Your choice (%d): ", allowed_attempts);
    else printf("Your choice: ");
}

void display_problem_details(FileData *data) {
    int index = get_problem_index(data);
    clear_screen();
    print_sudoku_grid(data->problems[index].grid);
    printf("\nProblem name: %s\n", data->problems[index].name);
    printf("Times played (total): %d\n", data->problems[index].times_played_total);
    printf("Times played (session): %d\n", data->problems[index].times_played_session);
    press_any_key_message("");
}