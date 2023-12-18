// name: António Dinis Myroshnyk
// description: Contains the functions that handle the file operations

#include "../include/file_operations.h"

#include <stdio.h>

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