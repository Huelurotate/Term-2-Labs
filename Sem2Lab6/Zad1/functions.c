#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "queue.h"

void menu(Node** tail)
{
	int menu_choice, is_running = 1;

	while (is_running)
	{
		print_menu();
		menu_option_choice(&menu_choice);
		switch (menu_choice)
		{
		case 1:
			input_queue(tail);
			break;
		case 2:
			display_queue(*tail);
			break;
		case 3:
			if (!is_empty(*tail))
				alt_input_queue(tail);
			else
				puts("\nQueue is empty.");
			break;
		case 4:
			is_running = 0;
			break;
		}
	}
}

void print_menu()
{
	puts("\n      MENU\n"
		"Choose an option:\n"
		"1 - Input Queue\n"
		"2 - Print Queue\n"
		"3 - Alternate Input Mode\n"
		"4 - Exit Program");
}

void menu_option_choice(int* choice)
{
	while (1)
	{
		int_input(choice);
		if (*choice < 1 || *choice > 4)
			puts("\nChoose an option(1-4).");
		else
			break;
	}
}

void input_queue(Node** tail)
{
	if (*tail != NULL)
		free_queue(tail);

	int queue_len;
	input_queue_length(&queue_len);

	input_queue_values(tail, queue_len);
}

void input_queue_length(int* len_var)
{
	printf("\nInput the queue length(max - %d):\n", MAX_QUEUE_LENGTH);
	while (1)
	{
		int_input(len_var);
		if (*len_var < 1 || *len_var > MAX_QUEUE_LENGTH)
			puts("\nInvalid Input.");
		else
			break;
	}
}

void input_queue_values(Node** tail, int len)
{
	int user_input;
	char c;

	for (int i = 0; i < len; i++)
	{
		printf("\nEnter value number %d(Enter - stop):\n", i + 1);

		if ((c = getchar()) == '\n')
			break;

		ungetc(c, stdin);
		int_input(&user_input);

		enqueue(tail, user_input);
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

void alt_input_queue(Node** tail)
{
	int user_input;
	int holster;
	char c;

	while(1)
	{
		puts("\nEnter a value to enqueue(Enter - stop):");

		if ((c = getchar()) == '\n')
			break;

		ungetc(c, stdin);
		int_input(&user_input);

		dequeue(tail, &holster);
		enqueue(tail, user_input);
	}
}