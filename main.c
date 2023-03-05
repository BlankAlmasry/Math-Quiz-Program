#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "main.h"

#define GAME_TIME 60
#define MAX_QUESTION_DIFFICULTY 12
enum operator_difficultly {
    ADDITION = 1, SUBTRACTION = 1, MULTIPLICATION = 2, DIVISION = 3
};

int main() {
    srand(time(NULL)); // Seed the random number generator with the current time
    time_t start_time = time(NULL); // Start time

    int i = 0, points_earned = 0, num_of_correct_answers = 0;
    while (1) {
        i++;

        int num1, num2;
        char operator;
        generateQuestion(&num1, &num2, &operator);

        int difficulty = calculate_difficulty(num1, num2, operator);

        printf("Question %d [Points %d]: %d %c %d = ", i + 1, difficulty, num1, operator, num2);

        double answer;
        while (scanf("%lf", &answer) != 1) {
            printf("Invalid input. Please enter a number.\n");
            i--;
            while (getchar() != '\n' && !feof(stdin)); // Clear the input buffer
        }
        time_t question_end_time = time(NULL);


        int correct_answer = calculateAnswer(num1, num2, operator);
        if (answer == correct_answer) {
            printf("Correct!\n");
            num_of_correct_answers++;
            points_earned += difficulty;
        } else {
            printf("Incorrect. The correct answer is %d.\n", correct_answer);
            points_earned -= MAX_QUESTION_DIFFICULTY + 1 - difficulty;
        }

        if (isTimeUp(start_time, question_end_time)) {
            printf("Time's up!\n");
            break;
        }

        display_time_remaining(start_time);
    }

    time_t end_time = time(NULL);
    long elapsed_time = end_time - start_time;


    printf("You answered %d out of %d questions correctly.\n", num_of_correct_answers, i);
    printf("Your points score is %d (correct answers: %d, elapsed time: %ld seconds).\n",
           points_earned, num_of_correct_answers, elapsed_time);

    return 0;
}

bool isTimeUp(time_t start_time, time_t question_end_time) { return question_end_time - start_time >= GAME_TIME; }

void generateQuestion(int *num1, int *num2, char *operator) {
    generateNumbers(num1, num2);
    (*operator) = generateOperator(*num1, *num2);
}

void generateNumbers(int *a, int *b) {
    (*a) = rand() % 50 + 1;
    (*b) = rand() % 50 + 1;
}

char generateOperator(int num1, int num2) {
    char operator;
    bool is_dividable = num1 % num2 == 0;
    switch (rand() % 4) {
        case 0:
            operator = '+';
            break;
        case 1:
            operator = '-';
            break;
        case 2:
            operator = '*';
            break;
        case 3:
            operator = is_dividable ? '/' : '*';
            break;
    }
    return operator;
}

int calculateAnswer(int a, int b, char operator) {
    int correct_answer;
    switch (operator) {
        case '+':
            correct_answer = a + b;
            break;
        case '-':
            correct_answer = a - b;
            break;
        case '*':
            correct_answer = a * b;
            break;
        case '/':
            correct_answer = a / b;
            break;
    }
    return correct_answer;
}

int calculate_difficulty(int a, int b, char operator) {
    return calculateOperatorDifficulty(operator) * calculateNumbersDifficulty(a, b);
}

int calculateNumbersDifficulty(int a, int b) {
    return (a * b < 10) ? 1 :
           (a * b < 100) ? 2 :
           (a * b < 1000) ? 3 : 4;
}

int calculateOperatorDifficulty(char operator) {
    int operator_difficulty = 0;

    switch (operator) {
        case '+':
            operator_difficulty = ADDITION;
            break;
        case '-':
            operator_difficulty = SUBTRACTION;
            break;
        case '*':
            operator_difficulty = MULTIPLICATION;
            break;
        case '/':
            operator_difficulty = DIVISION;
            break;
    }
    return operator_difficulty;
}

void display_time_remaining(time_t start_time) {
    long time_remaining = GAME_TIME - (time(NULL) - start_time);
    printf("Time remaining: %ld seconds.\n", time_remaining);
}
