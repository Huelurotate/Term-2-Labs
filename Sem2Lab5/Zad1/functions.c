#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "stack.h"

void menu(Node* stack1, Node* stack2)
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
				output_stacks(stack1, stack2);
			else
				puts("\nStacks are empty.");
			break;
		case 4:
			if (stack1 != NULL && stack2 != NULL)
				find_shared_elements(stack1, stack2);
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
		"4 - Print Shared Values\n"
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
		free_stack(stack);

	int stack_len;
	input_stack_length(&stack_len);

	input_stack_values(stack, stack_len);
}

void input_stack_length(int* len_var)
{
	printf("\nInput the Stack length(max - %d):\n", MAX_STACK_LEN);
	while (1) 
	{
		int_input(len_var);
		if (*len_var < 1 || *len_var > MAX_STACK_LEN)
			puts("\nInvalid Input.");
		else
			break;
	}
}

void input_stack_values(Node** stack, int stack_len)
{
	int user_input;
	char c;

	for(int i = 0; i < stack_len; i++)
	{
		printf("\nEnter value number %d(Enter - stop):\n", i + 1);
		
		if ((c = getchar()) == '\n')
			break;

		ungetc(c, stdin);
		int_input(&user_input);

		push(stack, user_input);
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

void output_stacks(Node* stack1, Node* stack2)
{
	display_stack(stack1, STACK_1);
	display_stack(stack2, STACK_2);
}

void display_stack(Node* top, int stack_number)
{
	if (top == NULL)
	{
		printf("\nStack %d is empty.\n", stack_number);
		return;
	}

	if(stack_number != 0)
		printf("\nSTACK %d:\n", stack_number);

	Node* temp = top;
	while (temp != NULL)
	{
		printf("%d\n", temp->data);
		temp = temp->next;
	}
}

void find_shared_elements(Node* stack1, Node* stack2)
{
	Node* temp_stack_1 = stack1;
	Node* temp_stack_2 = stack2;
	Node* result_stack = NULL;

	while (temp_stack_1 != NULL)
	{
		while (temp_stack_2 != NULL)
		{
			if ((temp_stack_2->data == temp_stack_1->data) && !in_result_stack(result_stack, temp_stack_2->data))
				push(&result_stack, temp_stack_2->data);

			temp_stack_2 = temp_stack_2->next;
		}

		temp_stack_1 = temp_stack_1->next;
		temp_stack_2 = stack2;
	}

	if (result_stack != NULL)
	{
		puts("\nShared stack values: ");
		display_stack(result_stack, DISPLAY_SHARED_ELEMENTS);
	}
	else puts("\nStacks do not share any values.");
}

int in_result_stack(Node* result_stack, int element)
{
	Node* temp = result_stack;
	while (temp != NULL)
	{
		if (temp->data == element)
			return 1;
		temp = temp->next;
	}

	return 0;
}