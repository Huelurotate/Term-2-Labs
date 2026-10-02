#pragma once

#include "queue.h"

#define MAX_QUEUE_LENGTH 100
#define CAPACITY 10

// MENU
void menu(Node** tail);
void print_menu();
void menu_option_choice(int* choice);

// INPUT
void input_queue(Node** tail);
void input_queue_length(int* len_var);
void input_queue_values(Node** tail, int len);

void int_input(int* var);

// ALTERNATE INPUT
void alt_input_queue(Node** tail);