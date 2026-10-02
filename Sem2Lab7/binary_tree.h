#pragma once

typedef struct TreeNode
{
	int value;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

TreeNode* create_node(int value);
void manual_insert(TreeNode** node, int value);
void ordered_insert(TreeNode** root, int value);

void auto_delete(TreeNode** root, int target_value);
void delete_deepest_node(TreeNode** root, TreeNode* deepest_node);

void manual_delete(TreeNode** root, int target_value);
TreeNode* find_target(TreeNode* root, int target_value);
TreeNode* find_parent(TreeNode* root, TreeNode* child);
TreeNode* find_extreme_right(TreeNode* root);
TreeNode* find_extreme_left(TreeNode* root);

void print_tree(TreeNode* root, int spaces);

void free_tree(TreeNode** root);
int is_empty(TreeNode* root);
void node_mem_alloc_check(TreeNode* memory_block);
