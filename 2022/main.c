#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <assert.h>
#include <malloc.h>

#include "day1/day1.h"
#include "day2/day2.h"
#include "day3/day3.h"
#include "day4/day4.h"

#define INPUT_FILE_FORMAT "%s\\day%u\\input.txt"

char *get_file_name(char *cwd, unsigned day) {
    // use snprintf because we want to write 0 characters of the result to NULL
    int size = snprintf(NULL, 0, INPUT_FILE_FORMAT, cwd, day);
    char *file = malloc(sizeof(char) * (size + 1)); // sprintf returns size of what should have been written, EXCLUDING null terminator
    assert(file != NULL);
    sprintf(file, INPUT_FILE_FORMAT, cwd, day);
    return file;
}

int main(void) {
    char work_dir[PATH_MAX];
    assert(getcwd(work_dir, sizeof(work_dir)) != NULL);
    printf("Current working directory: %s\n", work_dir);

    unsigned day = 4;

    char *file_name = get_file_name(work_dir, day);
    FILE *input_file = fopen(file_name, "r");
    assert(input_file != NULL);

    run4(input_file);

    fclose(input_file);
    free(file_name);
    return 0;
}