#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "stack.h"

void menu(Node* stack1, Node* stack2, Node* stack3)
{
	int menu_choice, is_running = 1;

	while (is_running)
	{
		print_menu();
		menu_option_choice(&menu_choice);
		switch (menu_choice)
		{
		case 1:
			input_stack(&stack1);
			break;
		case 2:
			input_stack(&stack2);
			break;
		case 3:
			if (stack1 != NULL || stack2 != NULL)
				output_stacks(stack1, stack2, stack3);
			else
				puts("\nStacks are empty.");
			break;
		case 4:
			if (stack1 != NULL && stack2 != NULL)
				build_third_stack(stack1, stack2, &stack3);
			else
				puts("\nStack(s) are empty.");
			break;
		case 5:
			is_running = 0;
			break;
		}
	}
}

void print_menu()
{
	puts("\n      MENU\n"
		"Choose an option:\n"
		"1 - Input Stack 1\n"
		"2 - Input Stack 2\n"
		"3 - Print Stacks\n"
		"4 - Build 3rd Stack\n"
		"5 - Exit Program");
}

void menu_option_choice(int* choice)
{
	while (1)
	{
		int_input(choice);
		if (*choice < 1 || *choice > 5)
			puts("\nChoose an option(1-5).");
		else
			break;
	}
}

void input_stack(Node** stack)
{
	if (*stack != NULL)
		stack_rewrite_request(stack);

	input_stack_values(stack);
}

void stack_rewrite_request(Node** stack)
{
	int rewrite_choice;
	puts("\nRewrite the Stack?(1 - Yes, 0 - No):");
	choice_loop(&rewrite_choice);

	if (rewrite_choice)
	{
		free_stack(stack);
		puts("\nStack was cleared.");
	}
}

void input_stack_values(Node** stack)
{
	int value;
	char c;

	while (1)
	{
		puts("\nEnter a value to push onto the Stack(Enter - Stop):");

		if ((c = getchar()) == '\n')
			return;

		ungetc(c, stdin);
		input_top_stack_value(*stack, &value);

		push(stack, value);
	}
}

void input_top_stack_value(Node* stack, int* value_var)
{
	if (stack != NULL)
	{
		while (1)
		{
			int_input(value_var);
			if (stack->data > *value_var)
				puts("\nEnter a value >= than the previous one");
			else
				break;
		}
	}
	else int_input(value_var);
}

void choice_loop(int* choice_var)
{
	while (1)
	{
		int_input(choice_var);
		if (*choice_var != 1 && *choice_var != 0)
			puts("\nInvalid Input. Please, choose an option(1 or 0).");
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

void output_stacks(Node* stack1, Node* stack2, Node* stack3)
{
	display_stack(stack1, STACK_1);
	display_stack(stack2, STACK_2);
	if (stack3 != NULL)
		display_stack(stack3, STACK_3);
}

void display_stack(Node* stack, int stack_number)
{
	if (stack == NULL)
	{
		printf("\nStack %d is empty.\n", stack_number);
		return;
	}

	printf("\nSTACK %d:\n", stack_number);

	Node* temp = stack;
	while (temp != NULL)
	{
		printf("%d\n", temp->data);
		temp = temp->next;
	}
}

void build_third_stack(Node* stack1, Node* stack2, Node** stack3)
{
	Node* temp_stack_1 = stack1;
	Node* temp_stack_2 = stack2;
	while (temp_stack_1 != NULL || temp_stack_2 != NULL)
	{
		if (temp_stack_2 == NULL && temp_stack_1 != NULL)
		{
			push(stack3, temp_stack_1->data);
			temp_stack_1 = temp_stack_1->next;
		}
		else if (temp_stack_1 == NULL && temp_stack_2 != NULL)
		{
			push(stack3, temp_stack_2->data);
			temp_stack_2 = temp_stack_2->next;
		}
		else if (temp_stack_1->data >= temp_stack_2->data)
		{
			push(stack3, temp_stack_1->data);
			temp_stack_1 = temp_stack_1->next;
		}
		else
		{
			push(stack3, temp_stack_2->data);
			temp_stack_2 = temp_stack_2->next;
		}	
	}

	reverse_stack(stack3);

	puts("\nStack 3 created.");
}

void reverse_stack(Node** stack)
{
	Node* prev = NULL;
	Node* cur = *stack;
	Node* next = NULL;

	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}

	*stack = prev;
}

void free_stacks(Node** stack1, Node** stack2, Node** stack3)
{
	free_stack(stack1);
	free_stack(stack2);
	free_stack(stack3);
}