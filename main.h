#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
int calculateAnswer(int a, int b, char operator);

char generateOperator(int num1, int num2);

void generateNumbers(int *a, int *b);

void generateQuestion(int *num1, int *num2, char *operator);

int calculate_difficulty(int a, int b, char operator);

void display_time_remaining(time_t question_start_time);

bool isTimeUp(time_t start_time, time_t question_end_time);

int calculateOperatorDifficulty(char operator);

int calculateNumbersDifficulty(int a, int b);
#endif //MAIN_H
