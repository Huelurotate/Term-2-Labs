#pragma once

typedef struct Node
{
	int data;
	struct Node* next;
} Node;

void push(Node** top, int value);
void pop(Node** top, int* var);
void peek(Node* top, int* var);
void free_stack(Node** top);