// name: António Dinis Myroshnyk
// description: Contains the functions that handle the file operations

#include "../include/file_operations.h"
#include "../include/sudoku.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *open_file(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if(!file) {
        printf("Failed to open %s file.\n", filename);
        exit(1);
    }
    return file;
}

void check_int_range(FileData *data, int value, int max, const char *message) {
    if(value < MIN_DATA_VALUE || value > max) {
        exit_error_message(data, message, -1, NULL);
    }
}

void check_success_rate(FileData *data, int value, int max, const char *message) {
    int calculated_success_rate = (int)((float)data->games_won / (float)data->games_played * 10000);
    if (calculated_success_rate != value) {
        message = "Mismatching success rate. Should be";
        exit_error_message(data, message, calculated_success_rate, NULL);
    } else if (value < MIN_DATA_VALUE || value > max) exit_error_message(data, message, -1, NULL);
}

char *read_line(FileData *data, char *buffer, int buffer_size) {
    char *comment, *trimmed;
    do {
        if (fgets(buffer, buffer_size, data->file) == NULL) {
            return NULL;
        }
        data->line_number++;
        comment = strstr(buffer, "//");
        if(comment) *comment = '\0';
        trimmed = trim(buffer);
    } while(trimmed[0] == '\0');
    return trimmed;
}

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
    FileData data = init_file_context("../data.txt");
    validate_statistics(&data);
    validate_problems(&data);
    validate_problem_count(&data);
    fclose(data.file);
}

void validate_statistics(FileData *data) {
    char buffer[FILE_BUFFER];
    char *trimmed = read_line(data, buffer, sizeof(buffer));
    int extra, decimal_part;
    printf("Debug: Game statistics line after removing comments and trimming: '%s'\n", trimmed);
    if(sscanf(trimmed, "%d %d %d.%d%n", &(data->games_played), &(data->games_won), &(data->success_rate), &decimal_part, &extra) != 4 || trimmed[extra] != '\0') {
        exit_error_message(data, "Invalid game statistics line.", -1, NULL);
    }
    data->success_rate = data->success_rate * 100 + decimal_part;
    check_int_range(data, decimal_part, 99, "Success rate has an invalid decimal part");
    check_int_range(data, data->games_played, INT_MAX, "Number of games played is less than 0.");
    check_int_range(data, data->games_won, data->games_played, "Number of games won is less than 0 or greater than number of games played.");
    check_success_rate(data, data->success_rate, 10000, "Success rate is less than 0 or greater than 100.");
    printf("Debug: Games played: %d, Games won: %d, Success rate: %.2f\n", data->games_played, data->games_won, (float)(data->success_rate) / 100);
}

void validate_problem_grid(FileData *data, int grid[GRID_SIZE]) {
    char buffer[FILE_BUFFER];
    for(int i = 0; i < GRID_SIZE; i++) {
        char *trimmed = read_line(data, buffer, sizeof(buffer));
        int extra;
        printf("Debug: Grid line after removing comments and trimming: '%s'\n", trimmed);
        if(sscanf(trimmed, "%d %d %d %d%n", &grid[0], &grid[1], &grid[2], &grid[3], &extra) != 4 ||trimmed[extra] != '\0') {
            exit_error_message(data, "Invalid grid line.", -1, NULL);
        }
        for(int j = 0; j < GRID_SIZE; j++) check_int_range(data, grid[j], GRID_SIZE, "Invalid grid value.");
        printf("Debug: Grid values: %d, %d, %d, %d\n", grid[0], grid[1], grid[2], grid[3]);
    }
}

void validate_problems(FileData *data) {
    char buffer[FILE_BUFFER], problem_name[USER_BUFFER], *trimmed;
    int times_played, grid[GRID_SIZE], games_played_across_problems = 0;
    while((trimmed = read_line(data, buffer, sizeof(buffer))) != NULL) {
        printf("Debug: Problem line after removing comments and trimming: '%s'\n", trimmed);
        if (sscanf(trimmed, "\"%[^\"]\" %d", problem_name, &times_played) != 2 || times_played < 0) {
            exit_error_message(data, "Invalid problem line.", -1, NULL);
        }
        printf("Debug: Problem name: '%s', Times played: %d\n", problem_name, times_played);
        validate_problem_grid(data, grid);
        games_played_across_problems += times_played;
        data->problem_count++;
    }
    validate_total_games_across_problems(data, games_played_across_problems);
}

char *trim(char *str) {
    char *end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0) return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return str;
}

void exit_error_message(FileData *data, const char *message, int print_check, int extra_values[2]) {
    if(print_check == -1) printf("Error on line %d: %s\n", data->line_number, message);
    else if(print_check == -2) {
        if(extra_values[0] < extra_values[1]) {
            printf("%s", message);
            printf(" Expected %d at most ", extra_values[0]);
            printf("but found %d.\n", extra_values[1]);
        }
        else {
            printf("%s", message);
            printf(" Expected %d ", extra_values[0]);
            printf("but found %d.\n", extra_values[1]);
        }
    }
    else printf("Error on line %d: %s %.2f\n", data->line_number, message, (float)(print_check) / 100);
    fclose(data->file);
    exit(1);
}

FileData init_file_context(const char *filename) {
    FileData data;
    data.file = open_file(filename, "r");
    data.line_number = data.games_played = data.games_won = data.success_rate = 0;
    return data;
}

void validate_problem_count(FileData *data) {
    if(data->problem_count > MAX_PROBLEMS) {
        int extra_values[2] = {MAX_PROBLEMS, data->problem_count};
        exit_error_message(data, "Maximum number of problems exceeded.", -2, extra_values);
    }
}

void validate_total_games_across_problems(FileData *data, int games_played_across_problems) {
    if(data->games_played != games_played_across_problems) {
        int extra_values[2] = {data->games_played, games_played_across_problems};
        exit_error_message(data, "Mismatching total number of games played.", -2, extra_values);
    }
}

//int count_problems() {
//    
//}
//
//void load_problems(SudokuProblem problems[]) {
//    
//}