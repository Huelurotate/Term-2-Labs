#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"
#include "queue.h"
#include "functions.h"

TreeNode* create_node(int value)
{
	TreeNode* new_node = malloc(sizeof(TreeNode));
	node_mem_alloc_check(new_node);

	new_node->left = NULL;
	new_node->right = NULL;
	new_node->value = value;

	return new_node;
}

// INSERTION
void manual_insert(TreeNode** node, int value)
{
	if (*node == NULL)
	{
		*node = create_node(value);
		return;
	}

	int side_choice;
	printf("\nCurrently on %d. Where to go/put(1 - Left, 2 - Right)?\n", (*node)->value);
	int_input(&side_choice);

	if (side_choice == 1)
		manual_insert(&((*node)->left), value);
	else
		manual_insert(&((*node)->right), value);
}

void ordered_insert(TreeNode** root, int value)
{
	TreeNode* new_node = create_node(value);
	if (*root == NULL)
	{
		*root = new_node;
		return;
	}

	QueueNode* tail = NULL;
	enqueue(&tail, *root);
	TreeNode* temp = NULL;

	while (tail != NULL)
	{
		TreeNode* current_node = tail->next->node_ptr;

		if (current_node->left == NULL)
		{
			current_node->left = new_node;
			break;
		}
		else enqueue(&tail, current_node->left);

		if (current_node->right == NULL)
		{
			current_node->right = new_node;
			break;
		}
		else enqueue(&tail, current_node->right);

		dequeue(&tail, &temp);
	}

	free_queue(&tail);
}

// AUTOMATIC DELETION
void auto_delete(TreeNode** root, int target_value)
{
	if ((*root)->left == NULL && (*root)->right == NULL)
	{
		if ((*root)->value == target_value)
		{
			puts("\nRoot was the target. Deleting root.");
			free(*root);
			*root = NULL;
			return;
		}
		puts("\nTarget value not found in the Tree.");
		return;
	}

	QueueNode* tail = NULL;
	enqueue(&tail, *root);

	TreeNode* target_node = NULL;
	TreeNode* current_node = NULL;

	while (tail != NULL)
	{
		dequeue(&tail, &current_node);

		if (current_node->value == target_value)
			target_node = current_node;
		if (current_node->left != NULL)
			enqueue(&tail, current_node->left);
		if (current_node->right != NULL)
			enqueue(&tail, current_node->right);
	}

	if (target_node != NULL)
	{
		if (target_node != current_node)
		{
			int saved_value = current_node->value;
			delete_deepest_node(root, current_node);
			target_node->value = saved_value;
		} else delete_deepest_node(root, current_node);
		puts("\nTarget value deleted.");
	}
	else puts("\nTarget value not found in the Tree.");

	free_queue(&tail);
}

void delete_deepest_node(TreeNode** root, TreeNode* deepest_node)
{
	if (*root == deepest_node)
	{
		free(*root);
		*root = NULL;
		return;
	}

	QueueNode* tail = NULL;
	enqueue(&tail, *root);
	
	TreeNode* current_node = NULL;

	while (tail != NULL)
	{
		dequeue(&tail, &current_node);

		if (current_node->right != NULL)
		{
			if (current_node->right == deepest_node)
			{
				free(current_node->right);
				current_node->right = NULL;
				free_queue(&tail);
				return;
			}
			else enqueue(&tail, current_node->right);
		}

		if (current_node->left != NULL)
		{
			if (current_node->left == deepest_node)
			{
				free(current_node->left);
				current_node->left = NULL;
				free_queue(&tail);
				return;
			}
			else enqueue(&tail, current_node->left);
		}
	}

	free_queue(&tail);
}

// MANUAL DELETION
void manual_delete(TreeNode** root, int target_value)
{
	TreeNode* target_node = find_target(*root, target_value);
	if (target_node == NULL)
	{
		puts("\nTarget value not found in the Tree.");
		return;
	}

	TreeNode* parent = find_parent(*root, target_node);

	int node_choice;
	printf("\nNode %d found. What child to promote(1 - Left, 2 - Right)?:\n", target_node->value);
	two_options_choice(&node_choice);

	TreeNode* new_child = NULL;

	if (node_choice == 1)
	{
		new_child = target_node->left;
		if (new_child != NULL && target_node->right != NULL)
		{
			TreeNode* extreme_right = find_extreme_right(new_child);
			extreme_right->right = target_node->right;
		}
		else if (new_child == NULL) new_child = target_node->right;
	}
	else
	{
		new_child = target_node->right;
		if (new_child != NULL && target_node->left != NULL)
		{
			TreeNode* extreme_left = find_extreme_left(new_child);
			extreme_left->left = target_node->left;
		}
		else if (new_child == NULL) new_child = target_node->left;
	}

	if (parent == NULL)
		*root = new_child;
	else if (parent->left == target_node)
		parent->left = new_child;
	else
		parent->right = new_child;

	free(target_node);
	puts("\nTarget value deleted.");
}

TreeNode* find_target(TreeNode* root, int target_value)
{
	QueueNode* tail = NULL;
	enqueue(&tail, root);

	TreeNode* current_node = NULL;
	TreeNode* result = NULL;

	while (tail != NULL)
	{
		dequeue(&tail, &current_node);

		if (current_node->value == target_value)
		{
			result = current_node;
			break;
		}
		if (current_node->left != NULL)
			enqueue(&tail, current_node->left);
		if (current_node->right != NULL)
			enqueue(&tail, current_node->right);
	}

	free_queue(&tail);
	return result;
}

TreeNode* find_parent(TreeNode* root, TreeNode* child)
{
	if (root == NULL || root == child) 
		return NULL;

	if (root->left == child || root->right == child)
		return root;

	TreeNode* result_left = find_parent(root->left, child);
	if (result_left)
		return result_left;
	
	return find_parent(root->right, child);
}

TreeNode* find_extreme_right(TreeNode* root)
{
	if (root == NULL) 
		return NULL;
	while (root->right != NULL)
		root = root->right;
	return root;
}

TreeNode* find_extreme_left(TreeNode* root)
{
	if (root == NULL)
		return NULL;
	while (root->left != NULL)
		root = root->left;
	return root;
}

// PRINTING
void print_tree(TreeNode* node, int spaces)
{
	if (node == NULL) return;

	spaces += 4;
	print_tree(node->right, spaces);

	puts("");
	for (int i = 0; i < spaces; i++)
		printf(" ");
	printf("%d\n", node->value);

	print_tree(node->left, spaces);
}

// MEMORY
void free_tree(TreeNode** root)
{
	if (*root == NULL) 
		return;

	free_tree(&((*root)->left));
	free_tree(&((*root)->right));

	free(*root);
	*root = NULL;
}

int is_empty(TreeNode* root)
{
	if (root == NULL)
		return 1;
	else
		return 0;
}

void node_mem_alloc_check(TreeNode* memory_block)
{
	if (memory_block == NULL)
	{
		puts("\nMemory allocation error.");
		exit(1);
	}
}