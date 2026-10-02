// ЗАДАНИЕ 2:
// Создать два стека для целых чисел. Первый стек – организовать ввод по возрастанию, 
// второй стек – организовать ввод по возрастанию.
// Без сортировок и переворачивания исходных стеков сформировать 
// третий стек упорядоченный по возрастанию.
// СТУДЕНТ: Яровиков Ю. В.
// ДАТА: 09.04.2026

#include <stdio.h>
#include "functions.h"
#include "stack.h"

int main()
{
	Node* stack1 = NULL;
	Node* stack2 = NULL;
	Node* stack3 = NULL;

	menu(stack1, stack2, stack3);

	free_stacks(&stack1, &stack2, &stack3);

	return 0;
}