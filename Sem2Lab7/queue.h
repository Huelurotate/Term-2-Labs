#pragma once

#include "binary_tree.h"

typedef struct QueueNode
{
	TreeNode* node_ptr;
	struct QueueNode* next;
} QueueNode;

void enqueue(QueueNode** tail, TreeNode* node_ptr);
void dequeue(QueueNode** tail, TreeNode** tree_node_var);
void free_queue(QueueNode** tail);