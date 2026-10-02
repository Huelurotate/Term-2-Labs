#pragma once

typedef struct Node
{
	char* data;
	struct Node* next;
} Node;

void enqueue(Node** tail, char* str);
void dequeue(Node** tail, int* var);
void display_queue(Node* tail);
void free_queue(Node** tail);
int is_empty(Node* tail);