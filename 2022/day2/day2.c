//
// Created by zaneb on 10/12/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "day2.h"

#define LOSE_SCORE 0
#define DRAW_SCORE 3
#define WIN_SCORE 6

enum Choice {
    ROCK,
    PAPER,
    SCISSORS
};

enum Choice decode_choice(char choice) {
    switch (choice) {
        case 'A':
            return ROCK;
        case 'B':
            return PAPER;
        case 'C':
            return SCISSORS;
        default:
            printf("Unknown choice %c\n", choice);
            exit(EXIT_FAILURE);
    }
}

enum Choice choice_score(enum Choice choice) {
    if (choice == ROCK) {
        return 1;
    } else if (choice == PAPER) {
        return 2;
    } else {
        return 3; // scissors
    }
}

enum Choice win_against(enum Choice choice) {
    if (choice == ROCK) {
        return PAPER;
    } else if (choice == PAPER) {
        return SCISSORS;
    } else {
        return ROCK; // rock wins against scissors
    }
}

enum Choice draw_against(enum Choice choice) {
    return choice;
}

enum Choice lose_against(enum Choice choice) {
    if (choice == ROCK) {
        return SCISSORS;
    } else if (choice == PAPER) {
        return ROCK;
    } else {
        return PAPER; // paper loses against scissors
    }
}

unsigned short outcome_score(enum Choice opponent, enum Choice player) {
    if (opponent == player) {
        return DRAW_SCORE;
    }

    return win_against(opponent) == player ? WIN_SCORE : LOSE_SCORE;
}

// PART 1

enum Choice decode_player_choice1(char choice) {
    if (choice == 'X') {
        return ROCK;
    } else  if (choice == 'Y') {
        return PAPER;
    } else if (choice == 'Z') {
        return SCISSORS;
    } else {
        printf("Unknown player choice (part 1): %c", choice);
        exit(EXIT_FAILURE);
    }
}

unsigned part1(char opponent_choice, char player_choice) {
    enum Choice opponent = decode_choice(opponent_choice);
    enum Choice player = decode_player_choice1(player_choice);
    return choice_score(player) + outcome_score(opponent, player);
}

// PART 2

unsigned part2(char opponent_choice, char outcome) {
    enum Choice opponent = decode_choice(opponent_choice);
    enum Choice player;
    if (outcome == 'X') {
        player = lose_against(opponent);
    } else  if (outcome == 'Y') {
        player = draw_against(opponent);
    } else if (outcome == 'Z') {
        player = win_against(opponent);
    } else {
        printf("Unknown outcome: %c", outcome);
        exit(EXIT_FAILURE);
    }

    return choice_score(player) + outcome_score(opponent, player);
}

void run2(FILE *file) {
    unsigned part1_score = 0;
    unsigned part2_score = 0;
    char char1 = '\0';
    char char2 = '\0';
    while (fscanf(file, "%c %c ", &char1, &char2) == 2) {
        part1_score += part1(char1, char2);
        part2_score += part2(char1, char2);
    }

    printf("Part 1 Total score: %u\n", part1_score);
    printf("Part 2 Total score: %u\n", part2_score);
}
