#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "day3.h"

#define LINE_MAX 50

/**
 * The alphabet, uppercase and lowercase
 */
#define ITEM_TYPES 52


typedef struct {
    char item;
    int count;

    /**
     * Unique tracker identifier of whatever last updated the count
     */
    int last_modifier;

} counter_t;

/**
 * Orders characters A-Z and a-z in sequential order starting at 0.
 */
int item_index(char item) {
    if (item >= 'A' && item <= 'Z') {
        return item - 'A';
    } else if (item >= 'a' && item <= 'z') {
        //                  Add this so that the item index of 'a' is right after the item index of 'Z'
        return item - 'a' + ('Z' - 'A') + 1;
    } else {
        printf("char outside of range: '%c' (ASCII %i)\n", item, item);
        exit(EXIT_FAILURE);
    }
}

/**
 * Lowercase item types a through z have priorities 1 through 26.
 * Uppercase item types A through Z have priorities 27 through 52.
 */
int item_priority(char item) {
    if (item >= 'A' && item <= 'Z') {
        return item - 38;
    } else if (item >= 'a' && item <= 'z') {
        return item - 96;
    } else {
        printf("char outside of range: %c (ASCII %i)\n", item, item);
        exit(EXIT_FAILURE);
    }
}

void print_counter(counter_t *counter) {
    printf("{%c, %i, %i}", counter->item, counter->count, counter->last_modifier);
}

void print_counters(counter_t *counters) {
    for (int i = 0; i < ITEM_TYPES; i++) {
        counter_t counter = counters[i];

        print_counter(&counter);
        printf(", ");
    }
    printf("\n");
}

counter_t *create_counters() {
    counter_t *counters = malloc(sizeof(counter_t) * ITEM_TYPES);
    assert(counters != NULL);
    for (char c = 'A'; c <= 'Z'; c++) {
        counters[item_index(c)] = (counter_t) {c, 0, -1};
    }
    for (char c = 'a'; c <= 'z'; c++) {
        counters[item_index(c)] = (counter_t) {c, 0, -1};
    }

    return counters;
}

counter_t *get_counter(counter_t *counters, char item) {
    int index = item_index(item);
    assert(index < ITEM_TYPES);
    return counters + index;
}

/**
 * @param item_lists An array of strings ending with null terminators
 * @param num_lists The length of the array of strings
 * @return the only character that is common between the different strings
 */
char find_common(char **item_lists, char num_lists) {

    counter_t *counters = create_counters();

    for (int list_i = 0; list_i < num_lists; list_i++) {

        char *string = item_lists[list_i];
        int length = strlen(string);

        for (int char_i = 0; char_i < length; char_i++) {
            char item = string[char_i];

            counter_t *counter = get_counter(counters, item);

            if (counter->last_modifier != list_i) {
                // The count has not been bumped by this string yet
                counter->count++;
                counter->last_modifier = list_i; // this string has bumped the count for this character
            }
        }
    }

    // The common character between the different strings
    char common = '\0';
    for (int i = 0; i < ITEM_TYPES; i++) {
        counter_t counter = counters[i];
        if (counter.count == num_lists) {
            if (common == '\0') {
                common = counter.item;
            } else {
                printf("More than one char in common: %c and %c", common, counter.item);
                exit(EXIT_FAILURE);
            }
        } else if (counter.count > num_lists) {
            printf("Count above %i for char '%c'. Expected no more than num_lists\n", num_lists, counter.item);
            exit(EXIT_FAILURE);
        }
    }

    if (common == '\0') {
        printf("Failed to find common char");
        exit(EXIT_FAILURE);
    }

    free(counters);

    return common;
}

void update_priority_sum(char **container_list, int container_amount, int *priority) {
    char group_common_item = find_common(container_list, container_amount);
    *priority += item_priority(group_common_item);
}

void separate_count(FILE *input) {
    char rucksack[LINE_MAX];
    int priority_sum = 0;

    char *comps[2] = {NULL, NULL};

    while (fgets(rucksack, LINE_MAX, input)) {
        int rucksack_size = strcspn(rucksack, "\n"); // counts chars until newline char is hit
        int compartment_size = rucksack_size / 2; // Two compartments per rucksack

        size_t mem_size = sizeof(char) * (compartment_size + 1); // +1 for null terminator that will be placed

        // Resize memory for compartments
        comps[0] = realloc(comps[0], mem_size);
        comps[1] = realloc(comps[1], mem_size);

        memcpy(comps[0], rucksack, mem_size); // Copy first half + random char from next
        memcpy(comps[1], rucksack + compartment_size, mem_size); // Copy second half + newline char

        comps[0][compartment_size] = '\0'; // Fix the last char of each
        comps[1][compartment_size] = '\0';

        update_priority_sum(comps, 2, &priority_sum);
    }

    free(comps[0]);
    free(comps[1]);

    printf("Priority sum form part 1: %u\n", priority_sum);
}



void group_count(FILE *input) {
    int priority_sum = 0;

    int elf_num = 0;
    char buffer[LINE_MAX] = {};
    char *rucksacks[3] = {NULL, NULL, NULL};

    while (fgets(buffer, LINE_MAX, input)) {
        if (elf_num > 2) {
            elf_num = 0; // New group

            // Calculate the common item of the previous group
            update_priority_sum(rucksacks, 3, &priority_sum);
        }

        int rucksack_len = strcspn(buffer, "\n");
        size_t mem_size = sizeof(char) * (rucksack_len + 1); // +1 for null terminator
        rucksacks[elf_num] = realloc(rucksacks[elf_num], mem_size);

        // Tried using strcpy_s but there was weird behaviour
        for (int i = 0; i < rucksack_len; i++) {
            rucksacks[elf_num][i] = buffer[i];
        }
        rucksacks[elf_num][rucksack_len] = '\0';

        elf_num ++;
    }

    update_priority_sum(rucksacks, 3, &priority_sum); // last iteration doesn't catch the last loop

    free(rucksacks[0]);
    free(rucksacks[1]);
    free(rucksacks[2]);

    printf("Priority sum from part 2: %i\n", priority_sum);
}

void run3(FILE *input) {

    separate_count(input);
    rewind(input);
    group_count(input);

}
