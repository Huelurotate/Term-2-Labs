#pragma once

typedef struct Node
{
    float data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct
{
    Node* front;
    Node* rear;
} Deque;

void init_deque(Deque* dq);
void insert_rear(Deque* dq, float value);
void delete_rear(Deque* dq, float* var);
void insert_front(Deque* dq, float value);
void delete_front(Deque* dq, float* var);
void display_deque(Deque* dq);
void free_deque(Deque* dq);
int is_empty(Deque* dq);
void check_deque_mem_alloc(Deque* dq);
void check_node_mem_alloc(Node* node);