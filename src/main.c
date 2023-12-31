// name: António Dinis Myroshnyk
// description: main file of the project containing the main loop

#include "../include/common.h"
#include "../include/file_operations.h"
#include "../include/sudoku.h"
#include "../include/statistics.h"
#include "../include/user_interface.h"

#include <stdio.h>
#include <string.h>

GameState game_state_init(FileData *data, int index) {
    GameState game;
    game.possible_errors = 2;
    game.completed = 0;
    memcpy(game.grid, data->problems[index].grid, sizeof(game.grid));
    strcpy(game.problem_name, data->problems[index].name);
    return game;
}

void add_new_problem(FileData *data) {
    if(check_problem_limit(data)) return;
    get_unique_problem_name(data, -1);
    get_sudoku_grid(data);
    write_problem_to_file(data);
}

void rename_problem(FileData *data) {
    display_problem_names(data);
    int index = get_problem_index(data);
    get_unique_problem_name(data, index);
    update_data_in_file(data, index);
}

void play_sudoku(FileData *data, int *prev_index) {
    int index = select_random_problem(data, prev_index);
    GameState game = game_state_init(data, index);
    data->games_played++;
    data->problems[index].times_played_total++;
    data->problems[index].times_played_session++;
    while(game.possible_errors > 0 && game.completed == 0) {
        int choice = menu(3, 2, &game, NULL);
        switch(choice) {
            case 1:
                place_number(&game, data);
                break;
            case 2:
                remove_number(game.grid, data->problems[index].grid);
                break;
            case 3:
                printf("You have forfeited the game.\n");
                game.completed = 1;
                break;
            default:
                printf("You should not be seeing this message. Please report this bug.\n");
                break;
        }
    }
    data->success_rate = (int)((float)data->games_won / (float)data->games_played * 10000);
    update_data_in_file(data, index);
}

void display_info(FileData *data) {
    display_stats(data);
    while(1) {
        int choice = menu(2, 3, NULL, data);
        switch(choice) {
            case 1:
                display_problem_details(data);
                break;
            case 2:
                return;
            default:
                printf("You should not be seeing this message. Please report this bug.\n");
                break;
        }
    }
}

void main_loop(FileData *data, int *prev_index) {
    while(1) {
        int choice = menu(5, 1, NULL, NULL);
        switch(choice) {
            case 1:
                play_sudoku(data, prev_index);
                break;
            case 2:
                add_new_problem(data);
                break;
            case 3:
                rename_problem(data);
                break;
            case 4:
                display_info(data);
                break;
            case 5:
                printf("Exiting the program.\n");
                return;
            default:
                printf("You should not be seeing this message. Please report this bug.\n");
                break;
        }
    }
}

int main() {
    generate_data_file();
    FileData data = validate_data_file();
    int prev_index = -1;
    main_loop(&data, &prev_index);
    return 0;
}