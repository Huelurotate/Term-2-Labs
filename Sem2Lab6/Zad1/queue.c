#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void enqueue(Node** tail, int value)
{
    Node* new_node = malloc(sizeof(Node));
    new_node->data = value;

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

void dequeue(Node** tail, int* var)
{
    if (is_empty(*tail))
    {
        puts("\nQueue is empty");
        return;
    }

    Node* head = (*tail)->next;
    *var = head->data;

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

void display_queue(Node* tail)
{
    if (is_empty(tail))
    {
        puts("\nQueue is empty");
        return;
    }

    puts("\nQueue elements are:");
    Node* temp = tail->next;
    do
    {
        printf("%d\n", temp->data);
        temp = temp->next;
    } while (temp != tail->next);
}

void free_queue(Node** tail)
{
    if (is_empty(*tail))
        return;

    Node* curr = (*tail)->next;
    Node* next_node;

    while (curr != *tail)
    {
        next_node = curr->next;
        free(curr);
        curr = next_node;
    }

    free(*tail);
    *tail = NULL;
}

int is_empty(Node* tail)
{
    if (tail == NULL)
        return 1;
    else 
        return 0;
}