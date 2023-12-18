// name: António Dinis Myroshnyk
// description: main file of the project containing the main loop

#include "../include/file_operations.h"
#include "../include/sudoku.h"
#include "../include/statistics.h"
#include "../include/user_interface.h"

#include <stdio.h>

void main_loop() {
    while(1) {
        const int max_recursion_depth = 5;
        int choice = main_menu(max_recursion_depth);
        switch(choice) {
            case 1:
                // implement play_sudoku function
                break;
            case 2:
                // implement add_new_problem function
                break;
            case 3:
                // implement rename_problem function
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
    main_loop();
    return 0;
}