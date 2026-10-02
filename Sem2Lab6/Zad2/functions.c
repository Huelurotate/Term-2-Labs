#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "deque.h"

void menu(Deque* deque)
{
    int menu_choice, is_running = 1;

    while (is_running)
    {
        print_menu();
        menu_option_choice(&menu_choice);
        switch (menu_choice)
        {
        case 1:
            input_deque(deque);
            break;
        case 2:
            display_deque(deque);
            break;
        case 3:
            if (!is_empty(deque))
                alt_input_deque(deque);
            else
                puts("\nDeque is empty.");
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
        "1 - Input Deque\n"
        "2 - Print Deque\n"
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

void input_deque(Deque* deque)
{
    if (!is_empty(deque))
        free_deque(deque);

    int deque_length;
    input_deque_length(&deque_length);
    input_deque_values(deque, deque_length);
}

void input_deque_length(int* len_var)
{
    printf("\nInput the deque length(max - %d):\n", MAX_DEQUE_LENGTH);
    while (1)
    {
        int_input(len_var);
        if (*len_var < 1 || *len_var > MAX_DEQUE_LENGTH)
            puts("\nInvalid Input.");
        else
            break;
    }
}

void input_deque_values(Deque* deque, int len)
{
    float user_input;
    char c;

    for (int i = 0; i < len; i++)
    {
        printf("\nEnter value number %d(Enter - stop):\n", i + 1);

        if ((c = getchar()) == '\n')
            break;

        ungetc(c, stdin);
        float_input(&user_input);

        insert_rear(deque, user_input);
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

void float_input(float* var)
{
    char buffer[100];
    char* endptr;
    float temp;

    while (1)
    {
        fgets(buffer, sizeof(buffer), stdin);

        buffer[strcspn(buffer, "\n")] = '\0';

        if (buffer[0] != '\0')
        {
            temp = strtof(buffer, &endptr);

            if (*endptr == '\0')
            {
                *var = temp;
                return;
            }
        }

        puts("\nInvalid Input. Please, enter a single float number.");
    }
}

void alt_input_deque(Deque* dq)
{
    float user_input;
    float holster;
    char c;

    while (1)
    {
        puts("\nEnter a value to insert(Enter - stop):");

        if ((c = getchar()) == '\n')
            break;

        ungetc(c, stdin);
        float_input(&user_input);

        delete_front(dq, &holster);
        insert_rear(dq, user_input);
    }
}