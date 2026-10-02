// ЗАДАНИЕ 3:
// Организовать три очереди с одинаковым количеством элементов, содержащие 
// соответствено имена, отчества и фамилии людей. Составьте очередь из элементов, 
// содержащих наиболее полную информацию о людях, воспользовавшись уже 
// созданными очередями и запросив какую-то дополнительную информацию.
// Решение в программе оформляйте через подпрограммы.
// СТУДЕНТ: Яровиков Ю. В.
// ДАТА: 17.04.2026

#include <stdio.h>
#include "functions.h"
#include "queue.h"

int main()
{
	Node* names = NULL;
	Node* middle_names = NULL;
	Node* surnames = NULL;
	Node* collection = NULL;

	menu(&names, &middle_names, &surnames, &collection);

	free_all_queues(&names, &middle_names, &surnames, &collection);

	return 0;
}