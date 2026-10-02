#pragma once

#include "stack.h"

#define STACK_1 1
#define STACK_2 2
#define STACK_3 3
#define CAPACITY 10

// MENU
void menu(Node* stack1, Node* stack2, Node* stack3);
void print_menu();
void menu_option_choice(int* choice);

// INPUT
void input_stack(Node** stack);
void stack_rewrite_request(Node** stack);
void input_stack_values(Node** stack);
void input_top_stack_value(Node* stack, int* value_var);

void choice_loop(int* choice_var);
void int_input(int* var);

// OUTPUT
void output_stacks(Node* stack1, Node* stack2, Node* stack3);
void display_stack(Node* stack, int stack_number);

// BUILD THIRD STACK
void build_third_stack(Node* stack1, Node* stack2, Node** stack3);
void reverse_stack(Node** stack);

// FREE STACKS
void free_stacks(Node** stack1, Node** stack2, Node** stack3);