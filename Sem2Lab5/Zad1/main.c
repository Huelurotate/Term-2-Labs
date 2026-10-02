// ЗАДАНИЕ 1:
// Создать два стека для целых чисел.
// Максимальные размеры стеков вводится с экрана.
// Вывести из первого стека все элементы, которые есть во втором стеке.
// СТУДЕНТ: Яровиков Ю. В.
// ДАТА: 08.04.2026

#include <stdio.h>
#include "functions.h"
#include "stack.h"

int main()
{
	Node* stack1 = NULL;
	Node* stack2 = NULL;
	
	menu(stack1, stack2);

	free_stack(&stack1);
	free_stack(&stack2);

	return 0;
}