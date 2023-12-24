// name: António Dinis Myroshnyk
// description: main file of the project containing the main loop

#include "../include/constants.h"
#include "../include/file_operations.h"
#include "../include/sudoku.h"
#include "../include/statistics.h"
#include "../include/user_interface.h"

#include <stdio.h>

void add_new_problem(FileData *data) {
    get_unique_problem_name(data, -1);
    get_sudoku_grid(data);
    write_problem_to_file(data);
}

void rename_problem(FileData *data) {
    int index = get_problem_index(data);
    get_unique_problem_name(data, index);
    update_problem_in_file(data, index);
}

void main_loop(FileData *data) {
    while(1) {
        int choice = main_menu(MAX_RECURSION_DEPTH);
        switch(choice) {
            case 1:
                //play_sudoku();
                break;
            case 2:
                add_new_problem(data);
                break;
            case 3:
                rename_problem(data);
                break;
            case 4:
                // implement view_statistics function
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
    main_loop(&data);
    return 0;
}