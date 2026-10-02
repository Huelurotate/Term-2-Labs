// ЗАДАНИЕ: Структура содержит информацию о клиентах банка: 
// номер паспорта (число), фамилию (указатель), 
// вложенное объединение – номер счёта (строка фиксированной длины) и сумму вклада. 
// Найти максимальную сумму вклада. Удалить клиентов с заданным номером счёта.
// СТУДЕНТ: Яровиков Ю. В.
// ДАТА: 01.04.2026

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main()
{
	Bank_Info* bank_info_arr = malloc(sizeof(Bank_Info));
	struct_alloc_check(bank_info_arr);

	menu(bank_info_arr);

	return 0;
}