#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "queue.h"
#include "binary_tree.h"

void menu(TreeNode** root)
{
	int menu_choice, is_running = 1;

	while (is_running)
	{
		print_menu();
		menu_option_choice(&menu_choice);
		switch (menu_choice)
		{
		case 1:
			create_new_tree(root);
			break;
		case 2:
			if (!is_empty(*root))
				input_tree(root);
			else
				puts("\nTree is empty.");
			break;
		case 3:
			if (!is_empty(*root))
				delete_tree_value(root);
			else
				puts("\nTree is empty.");
			break;
		case 4:
			if (!is_empty(*root))
			{
				printf("\nBinary Tree:");
				print_tree(*root, 0);
			}
			else puts("\nTree is empty.");
			break;
		case 5:
			if (!is_empty(*root))
				count_nodes_leaves(*root);
			else
				puts("\nTree is empty.");
			break;
		case 6:
			is_running = 0;
			break;
		}
	}
}

void print_menu()
{
	puts("\n      MENU\n"
		"Choose an option:\n"
		"1 - Create New Binary Tree\n"
		"2 - Add New Element\n"
		"3 - Delete Element\n"
		"4 - Print Binary Tree\n"
		"5 - Count Nodes and Leaves\n"
		"6 - Exit Program");
}

void menu_option_choice(int* choice)
{
	while (1)
	{
		int_input(choice);
		if (*choice < 1 || *choice > 6)
			puts("\nChoose an option(1-6).");
		else
			break;
	}
}

void create_new_tree(TreeNode** root)
{
	if (!is_empty(*root))
		free_tree(root);

	puts("\nNew binary tree will be created.");
	
	int root_value;
	puts("Enter the root value:");
	int_input(&root_value);

	*root = create_node(root_value);
}

void input_tree(TreeNode** root)
{
	int new_value;
	puts("\nEnter a value to insert:");
	int_input(&new_value);

	int user_choice;
	puts("\nWhat insert method to use(1 - Manual, 2 - Ordered)?:");
	two_options_choice(&user_choice);

	if (user_choice == 1)
		manual_insert(root, new_value);
	else
		ordered_insert(root, new_value);
}

void delete_tree_value(TreeNode** root)
{
	int target_value;
	puts("\nEnter a value to delete:");
	int_input(&target_value);

	int user_choice;
	puts("\nWhat restructuring method to use(1 - Manual, 2 - Automatic)?:");
	two_options_choice(&user_choice);

	if (user_choice == 1)
		manual_delete(root, target_value);
	else
		auto_delete(root, target_value);
}

void two_options_choice(int* choice)
{
	while (1)
	{
		int_input(choice);
		if (*choice < 1 || *choice > 2)
			puts("\nChoose an option(1-2).");
		else
			break;
	}
}

void int_input(int* var)
{
	char buffer[100];
	char* endptr;
	long temp;

	while (1)
	{
		fgets(buffer, sizeof(buffer), stdin);

		buffer[strcspn(buffer, "\n")] = '\0';

		if (buffer[0] != '\0')
		{
			temp = strtol(buffer, &endptr, CAPACITY);

			if (*endptr == '\0')
			{
				*var = (int)temp;
				return;
			}
		}

		puts("\nInvalid Input. Please, enter a single integer.");
	}
}

void count_nodes_leaves(TreeNode* root)
{
	QueueNode* tail = NULL;
	enqueue(&tail, root);

	int level = 0;
	while (tail != NULL)
	{
		int total_nodes = 0;
		QueueNode* head = tail->next;
		do
		{
			total_nodes++;
			head = head->next;
		} while (head != tail->next);

		int leaf_count = 0;
		int internal_nodes_count = 0;
		
		for (int i = 0; i < total_nodes; i++)
		{
			TreeNode* current_node = NULL;
			dequeue(&tail, &current_node);

			if (current_node == NULL)
				continue;

			if (current_node->left == NULL && current_node->right == NULL)
				leaf_count++;
			else
				internal_nodes_count++;

			if (current_node->left != NULL)
				enqueue(&tail, current_node->left);
			if (current_node->right != NULL)
				enqueue(&tail, current_node->right);
		}

		printf("\nLevel: %d Internal Nodes: %d Leaves: %d", level, internal_nodes_count, leaf_count);
		level++;
	}
	puts("");
}