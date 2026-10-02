#pragma once

#include "binary_tree.h"

#define CAPACITY 10

// MENU
void menu(TreeNode** root);
void print_menu();
void menu_option_choice(int* choice);

// CREATE NEW TREE
void create_new_tree(TreeNode** root);

// INPUT
void input_tree(TreeNode** root);

// DELETION
void delete_tree_value(TreeNode** root);

// COUNTING
void count_nodes_leaves(TreeNode* root);

void two_options_choice(int* choice);

void int_input(int* var);