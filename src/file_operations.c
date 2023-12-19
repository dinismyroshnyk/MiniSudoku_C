// name: António Dinis Myroshnyk
// description: Contains the functions that handle the file operations

#include "../include/file_operations.h"
#include "../include/sudoku.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void generate_data_file() {
    FILE *file = fopen("../data.txt", "r");
    if(file) fclose(file);
    else {
        file = fopen("../data.txt", "w");
        if(file) {
            fprintf(file, "// this is a comment, it will be ignored by the program\n\n");
            fprintf(file, "0 0 0.0 // total number of games played, number of games won, success rate\n\n");
            fprintf(file, "\"Hardcoded Problem 1\" 0 // name of the problem, times played this problem\n");
            fprintf(file, "2 0 3 0\n0 3 0 2\n3 0 4 0\n1 4 0 0\n\n");
            fprintf(file, "\"Hardcoded Problem 2\" 0\n");
            fprintf(file, "4 3 0 1\n0 0 3 0\n0 4 0 3\n3 0 4 0\n");
            fclose(file);
        } else printf("Failed to create data.txt file.\n");
    }
}

void validate_data_file() {
    FILE *file = fopen("../data.txt", "r");
    if(!file) {
        printf("Failed to open data.txt file.\n");
        exit(1);
    }

    char buffer[256], problem_name[40];
    int games_played, games_won, times_played;
    float success_rate;

    // Read and validate the game statistics line
    fgets(buffer, sizeof(buffer), file);
    char *comment = strstr(buffer, "//");
    if (comment) *comment = '\0'; // Remove trailing comment
    char *trimmed = trim(buffer); // Trim leading and trailing spaces
    printf("Debug: Game statistics line after removing comments and trimming: '%s'\n", trimmed);
    if (sscanf(trimmed, "%d %d %f", &games_played, &games_won, &success_rate) != 3) {
        printf("Invalid game statistics line.\n");
        exit(1);
    }
    if (games_played < games_won) {
        printf("Number of games played is less than number of games won.\n");
        exit(1);
    }
    if (games_played < 0) {
        printf("Number of games played is less than 0.\n");
        exit(1);
    }
    if (games_won < 0) {
        printf("Number of games won is less than 0.\n");
        exit(1);
    }
    if (success_rate < 0 || success_rate > 100) {
        printf("Success rate is not between 0 and 100.\n");
        exit(1);
    }
    printf("Debug: Games played: %d, Games won: %d, Success rate: %.2f\n", games_played, games_won, success_rate);

    // Read and validate the problems
    while (fgets(buffer, sizeof(buffer), file)) {
        // Remove trailing comment
        comment = strstr(buffer, "//");
        if (comment) *comment = '\0';

        // Trim leading and trailing spaces
        trimmed = trim(buffer);

        // Ignore empty lines
        if (trimmed[0] == '\0') {
            continue;
        }

        printf("Debug: Problem line after removing comments and trimming: '%s'\n", trimmed);

        // Validate the problem name and times played
        if (sscanf(trimmed, "\"%[^\"]\" %d", problem_name, &times_played) != 2 || times_played < 0) {
            printf("Invalid problem line.\n");
            exit(1);
        }
        printf("Debug: Problem name: '%s', Times played: %d\n", problem_name, times_played);

        // Validate the problem grid
        for (int i = 0; i < 4; i++) {
            fgets(buffer, sizeof(buffer), file);
            comment = strstr(buffer, "//");
            if (comment) *comment = '\0';
            trimmed = trim(buffer);
            printf("Debug: Grid line after removing comments and trimming: '%s'\n", trimmed);
            int grid[4];
            if (sscanf(trimmed, "%d %d %d %d", &grid[0], &grid[1], &grid[2], &grid[3]) != 4) {
                printf("Invalid grid line.\n");
                exit(1);
            }
            for (int j = 0; j < 4; j++) {
                if (grid[j] < 0 || grid[j] > 4) {
                    printf("Invalid grid value.\n");
                    exit(1);
                }
            }
            printf("Debug: Grid values: %d, %d, %d, %d\n", grid[0], grid[1], grid[2], grid[3]);
        }
    }

    fclose(file);
}

char *trim(char *str) {
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

//int count_problems() {
//    
//}
//
//void load_problems(SudokuProblem problems[]) {
//    
//}