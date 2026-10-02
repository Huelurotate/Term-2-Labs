#pragma once

#include "stack.h"

#define MAX_STACK_LEN 100
#define STACK_1 1
#define STACK_2 2
#define DISPLAY_SHARED_ELEMENTS 0
#define CAPACITY 10

// MENU
void menu(Node* stack1, Node* stack2);
void print_menu();
void menu_option_choice(int* choice);

// INPUT
void input_stack(Node** stack);
void input_stack_length(int* len_var);
void input_stack_values(Node** stack, int stack_len);

void int_input(int* var);

// OUTPUT
void output_stacks(Node* stack1, Node* stack2);
void display_stack(Node* top, int stack_number);

// FIND
void find_shared_elements(Node* stack1, Node* stack2);
int in_result_stack(Node* result_stack, int element);