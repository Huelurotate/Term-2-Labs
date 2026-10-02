// ЗАДАНИЕ 2:
// Создать дек для плавающих чисел.Максимальный размер дека вводится с экрана.
// Создать функции для ввода и вывода элементов дека.Ввести в дек числа с экрана.
// После этого перейти в режим ввода, при котором перед занесением 
// элемента происходит удаление левого элемента.
// СТУДЕНТ: Яровиков Ю. В.
// ДАТА: 16.04.2026

#include <stdlib.h>
#include "functions.h"
#include "deque.h"

int main()
{
	Deque* main_deque = malloc(sizeof(Deque));
	check_deque_mem_alloc(main_deque);

	init_deque(main_deque);

	menu(main_deque);

	free_deque(main_deque);
	free(main_deque);

	return 0;
}