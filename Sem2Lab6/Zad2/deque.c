#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

void init_deque(Deque* dq)
{
    dq->front = NULL;
    dq->rear = NULL;
}

void insert_rear(Deque* dq, float value)
{
    Node* new_node = malloc(sizeof(Node));
    check_node_mem_alloc(new_node);
    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = dq->rear;

    if (dq->rear == NULL)
    {
        dq->front = dq->rear = new_node;
    }
    else
    {
        dq->rear->next = new_node;
        dq->rear = new_node;
    }
}

void delete_rear(Deque* dq, float* var)
{
    if (is_empty(dq))
    {
        puts("\nDeque is empty.");
        return;
    }

    Node* temp = dq->rear;
    *var = temp->data;

    dq->rear = dq->rear->prev;

    if (dq->rear == NULL)
        dq->front = NULL;
    else
        dq->rear->next = NULL;

    free(temp);
}

void insert_front(Deque* dq, float value)
{
    Node* new_node = malloc(sizeof(Node));
    check_node_mem_alloc(new_node);
    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = dq->front;

    if (dq->front == NULL)
    {
        dq->front = dq->rear = new_node;
    }
    else
    {
        dq->front->prev = new_node;
        dq->front = new_node;
    }
}

void delete_front(Deque* dq, float* var)
{
    if (is_empty(dq))
    {
        puts("\nDeque is empty.");
        return;
    }

    Node* temp = dq->front;
    *var = temp->data;

    dq->front = dq->front->next;

    if (dq->front == NULL)
        dq->rear = NULL;
    else
        dq->front->prev = NULL;

    free(temp);
}

void display_deque(Deque* dq)
{
    if (is_empty(dq))
    {
        puts("\nDeque is empty.");
        return;
    }

    Node* temp = dq->front;

    puts("\nDeque values:");
    while (temp != NULL)
    {
        printf("%.3f\n", temp->data);
        temp = temp->next;
    }
    puts("");
}

void free_deque(Deque* dq)
{
    if (is_empty(dq))
        return;

    Node* curr = dq->front;
    Node* next_node;

    while (curr != NULL)
    {
        next_node = curr->next;
        free(curr);
        curr = next_node;
    }

    dq->front = NULL;
    dq->rear = NULL;
}

int is_empty(Deque* dq)
{
    if (dq == NULL || dq->front == NULL || dq->rear == NULL)
        return 1;
    else
        return 0;
}

void check_deque_mem_alloc(Deque* dq)
{
    if (dq == NULL)
    {
        puts("\nMemory Allocation Error.");
        exit(1);
    }
}

void check_node_mem_alloc(Node* node)
{
    if (node == NULL)
    {
        puts("\nMemory Allocation Error.");
        exit(1);
    }
}