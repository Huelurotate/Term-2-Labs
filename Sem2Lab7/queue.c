#include <stdlib.h>
#include "queue.h"

void enqueue(QueueNode** tail, TreeNode* node_ptr)
{
	QueueNode* new_node = malloc(sizeof(QueueNode));
	new_node->node_ptr = node_ptr;

	if (*tail == NULL)
	{
		*tail = new_node;
		new_node->next = new_node;
	}
	else
	{
		new_node->next = (*tail)->next;
		(*tail)->next = new_node;
		*tail = new_node;
	}
}

void dequeue(QueueNode** tail, TreeNode** tree_node_var)
{
	if (*tail == NULL) return;

	QueueNode* head = (*tail)->next;
	*tree_node_var = head->node_ptr;

	if (head == *tail)
	{
		free(head);
		*tail = NULL;
	}
	else
	{
		(*tail)->next = head->next;
		free(head);
	}
}

void free_queue(QueueNode** tail)
{
	if (*tail == NULL) return;
	
	QueueNode* curr = (*tail)->next;
	QueueNode* next_node;

	while (curr != *tail)
	{
		next_node = curr->next;
		free(curr);
		curr = next_node;
	}

	free(*tail);
	*tail = NULL;
}