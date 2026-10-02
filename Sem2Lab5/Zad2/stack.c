#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void push(Node** top, int value)
{
	Node* new_node = malloc(sizeof(Node));

	new_node->data = value;
	new_node->next = *top;

	*top = new_node;
}

void pop(Node** top, int* var)
{
	if (*top == NULL)
	{
		puts("\nStack Underflow.");
		return;
	}

	Node* temp = *top;
	*var = temp->data;

	*top = temp->next;
	free(temp);
}

void peek(Node* top, int* var)
{
	if (top == NULL)
	{
		puts("\nStack is empty.");
		return;
	}

	*var = top->data;
}

void free_stack(Node** top)
{
	Node* temp;
	while (*top != NULL)
	{
		temp = *top;
		*top = (*top)->next;
		free(temp);
	}
}