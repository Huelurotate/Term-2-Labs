#pragma once

#include "deque.h"

#define MAX_DEQUE_LENGTH 100
#define CAPACITY 10

// MENU
void menu(Deque* deque);
void print_menu();
void menu_option_choice(int* choice);

// INPUT
void input_deque(Deque* deque);
void input_deque_length(int* len_var);
void input_deque_values(Deque* deque, int len);

void int_input(int* var);
void float_input(float* var);

// ALTERNATE INPUT MODE
void alt_input_deque(Deque* dq);