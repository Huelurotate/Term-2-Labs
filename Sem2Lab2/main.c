#include <stdio.h>
#include "functions.h"

int main()
{
	char* filename;
	int file_exist = 0;
	create_filename(&filename, &file_exist, NEED_FILENAME);

	print_message(file_exist);

	menu(filename, file_exist);

	free(filename);

	return 0;
}