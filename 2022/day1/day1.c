#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 10
#define TRACKED_CAL_COUNT 3

void run1(FILE *input) {

    // A "leaderboard of maximum calories
    unsigned top_calories[TRACKED_CAL_COUNT] = {};

    // Iteration specific
    char line[MAX_LINE_LENGTH];
    unsigned line_number = 0;
    unsigned calorie_sum = 0; // Total amount of calories for an elf

    while (fgets(line, MAX_LINE_LENGTH, input)) {
        unsigned calories = 0; // Number of calories listed on this specific line
        int result = sscanf(line, "%u", &calories);

        if (result == 1) {
            // Got one number match

            calorie_sum += calories;

        } else if (result == -1) {
            // Blank line - separates two sets of calorie counts

            // Check if the last set of calories was greater than the maximum so far
            for (int i = 0; i < TRACKED_CAL_COUNT; i++) {
                if (calorie_sum == top_calories[i]) {
                    break; // This amount of calories is already on the "leaderboard"
                }

                if (calorie_sum > top_calories[i]) {
                    // New max

                    // Shuffle the list to allow room for the new max
                    for (int j = TRACKED_CAL_COUNT - 1; j > i; j--) {
                        top_calories[j] = top_calories[j - 1];
                    }

                    // Insert new max
                    top_calories[i] = calorie_sum;
                    break;
                }
            }

            calorie_sum = 0;

        } else {
            printf("Got unexpected value on line number %u\n", line_number);
            exit(EXIT_FAILURE);
        }

        line_number++;
    }

    unsigned tracked_calorie_sum = 0;
    printf("Max calories:\n");
    for (int i = 0; i < TRACKED_CAL_COUNT; i++) {
        printf("%i. %i\n", i + 1, top_calories[i]);
        tracked_calorie_sum += top_calories[i];
    }

    printf("\nSum of the above: %u", tracked_calorie_sum);
}
