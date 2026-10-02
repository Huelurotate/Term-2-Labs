#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void create_filename(char** filename_var, int* file_exist_var, int new_filename_flag)
{
	*filename_var = malloc(1);
	check_char_alloc(*filename_var);

	int len = 0;
	while (1)
	{
		filename_input(filename_var, &len);

		if (len >= EXTENSION_LEN && strcmp(".txt", (*filename_var + (len - EXTENSION_LEN))) == 0)
		{
			check_file_exist(*filename_var, file_exist_var);
			if (*file_exist_var && new_filename_flag)
			{
				puts("\nPlease, enter a new filename.");
			}
			else break;
		}
	}
}

void filename_input(char** str, int* length)
{
	do
	{
		puts("\nPlease, enter a filename with a .txt extension:");
		str_input(str, length);
	} while (*length == 0);
}

void str_input(char** str, int* length)
{
	*length = 0;
	char c;
	while ((c = getchar()) != '\n')
	{
		(*length)++;
		*str = realloc(*str, (*length + 1) * sizeof(char));
		check_char_alloc(*str);
		(*str)[*length - 1] = c;
	}

	(*str)[*length] = '\0';
}

void check_char_alloc(char* memory_block)
{
	if (memory_block == NULL)
	{
		puts("Memory allocation error.");
		exit(1);
	}
}

void check_file_exist(char* filename_var, int* flag)
{
	FILE* txt_file = fopen(filename_var, "r");
	if (txt_file != NULL)
	{
		*flag = 1;
		fclose(txt_file);
	}
	else *flag = 0;
}

void print_message(int file_exist_var)
{
	if (file_exist_var)
		puts("\nAn existing file was chosen.");
	else
		puts("\nA new file will be created.");
}

void menu(char* filename, int file_exist_var)
{
	int menu_choice, is_running = 1;
	int has_numbers = 0;

	if (file_exist_var)
		has_numbers = 1;

	while (is_running)
	{
		print_menu();
		menu_option_choice(&menu_choice);
		switch (menu_choice)
		{
		case 1:
			file_input(filename, &has_numbers, file_exist_var);
			break;
		case 2:
			if (has_numbers)
				output_file(filename);
			else
				puts("\nThe file is empty.");
			break;
		case 3:
			if (has_numbers)
				print_file_even(filename);
			else
				puts("\nThe file is empty.");
			break;
		case 4:
			if (has_numbers)
				multiply_two_file_numbers(filename);
			else
				puts("\nThe file is empty.");
			break;
		case 5:
			is_running = 0;
			break;
		}
	}
}

void print_menu()
{
	puts("\n      MENU\n"
		"Choose an option:\n"
		"1 - Write To The File\n"
		"2 - Print File Contents\n"
		"3 - Print Even Numbers\n"
		"4 - Multiply First Two Numbers\n"
		"5 - Exit Program");
}

void menu_option_choice(int* choice)
{
	while (scanf_s("%d", choice) != 1 || *choice < 1 || *choice > 5)
	{
		puts("Invalid Input.");
		rewind(stdin);
	}
	rewind(stdin);
}

void file_input(char* filename, int* has_numbers, int file_exist_var)
{
	int user_input_choice = WRITE_CHOICE;

	if (*has_numbers || file_exist_var)
		input_mode_choice(&user_input_choice);

	manual_file_input(filename, has_numbers, user_input_choice);
}

void manual_file_input(char* filename, int* has_numbers, int user_input_choice)
{
	FILE* txt_file;

	select_file_open_mode(&txt_file, filename, has_numbers, user_input_choice);

	file_opening_check(txt_file);

	while (1)
	{
		puts("\nEnter a number to write into the file:");

		char char_input = getchar();

		if (char_input == '\n')
			break;

		ungetc(char_input, stdin);

		int num;
		int_input_loop(&num);

		fprintf(txt_file, " %d", num);
		*has_numbers = 1;
	}

	fclose(txt_file);
}

void select_file_open_mode(FILE** file, char* filename_var, int* has_numbers, int user_input_var)
{
	if ((*has_numbers && user_input_var == WRITE_CHOICE) || !(*has_numbers))
	{
		*file = fopen(filename_var, "w");
		file_opening_check(*file);
		*has_numbers = 0;
	}
	else if (*has_numbers && user_input_var == APPEND_CHOICE)
	{
		*file = fopen(filename_var, "a");
		file_opening_check(*file);
	}
}

void input_mode_choice(int* choice)
{
	printf("\nWrite or Append to the file?(1 - Write, 0 - Append): ");
	choice_loop(choice);
}

void choice_loop(int* choice_var)
{
	while (scanf_s("%d", choice_var) != 1 || (*choice_var != 0 && *choice_var != 1))
	{
		puts("Invalid Input.");
		rewind(stdin);
	}
	rewind(stdin);
}

void int_input_loop(int* var)
{
	while (scanf_s("%d", var) != 1)
	{
		printf("Invalid Input.\n");
		rewind(stdin);
	}
	rewind(stdin);
}

void output_file(char* filename)
{
	FILE* txt_file = fopen(filename, "r");
	file_opening_check(txt_file);

	puts("\nContents of the file are:");

	int num;
	while(fscanf(txt_file, "%d", &num) == 1)
		printf("%d ", num);

	puts("");
	fclose(txt_file);
}

void print_file_even(char* filename)
{
	FILE* txt_file = fopen(filename, "r");
	file_opening_check(txt_file);

	puts("\nEven numbers in the file are:");

	int num;
	int is_found = 0;
	while (fscanf(txt_file, "%d", &num) == 1)
	{
		if (num % 2 == 0)
		{
			printf("%d ", num);
			is_found = 1;
		}
	}
	
	if (!is_found)
		puts("\nFile has no even numbers.");
	else
		puts("");

	fclose(txt_file);
}

void multiply_two_file_numbers(char* main_filename)
{
	int x, y, has_two_numbers = 1;
	get_two_file_numbers(main_filename, &x, &y, &has_two_numbers);
	if (!has_two_numbers)
	{
		printf("\nFile %s does not have two numbers.\n", main_filename);
		return;
	}

	char* new_filename;
	int file_exist = 0;
	create_filename(&new_filename, &file_exist, NEED_NEW_FILENAME);
	
	int width;
	find_width(&width, x, y);

	print_multiplication(new_filename, x, y, width);

	printf("\nFile %s now includes the multiplication of %d and %d.\n", \
			new_filename, x, y);
}

void get_two_file_numbers(char* filename, int* var1, int* var2, int* flag)
{
	FILE* txt_file = fopen(filename, "r");
	file_opening_check(txt_file);

	get_file_number(txt_file, var1, flag);
	get_file_number(txt_file, var2, flag);
}

void get_file_number(FILE* file_var, int* var, int* flag)
{
	if (fscanf(file_var, "%d", var) != 1)
		*flag = 0;
}

void find_width(int* total_width, int num1, int num2)
{
	int additional_width = 0;

	if ((num1 < 0 && num2 >= 0) || (num2 < 0 && num1 >= 0))
		additional_width++;

	*total_width = count_digits(num1) + count_digits(num2) + additional_width;
}

int count_digits(int num)
{
	int total_digits = 1;
	if (num < 0)
		num *= (-1);

	while (num > (CAPACITY - 1))
	{
		num /= CAPACITY;
		total_digits++;
	}

	return total_digits;
}

void print_multiplication(char* filename, int num1, int num2, int width)
{
	FILE* txt_file = fopen(filename, "w");
	file_opening_check(txt_file);

	print_two_numbers(txt_file, num1, num2, width);
	print_lines(txt_file, width);

	print_summing(txt_file, num1, num2, width);
	print_lines(txt_file, width);

	fprintf(txt_file, "%*d", width, (num1 * num2));
	fclose(txt_file);
}

void print_two_numbers(FILE* file, int num1, int num2, int width)
{
	print_number(file, num1, width);
	print_mult_symbol(file, width, num1, num2);
	print_number(file, num2, width);
}

void print_number(FILE* file, int number, int width)
{
	fprintf(file, "%*d", width, number);
	putc('\n', file);
}

void print_mult_symbol(FILE* file, int width, int num1, int num2)
{
	int shift = (num1 > num2) ? count_digits(num1) : count_digits(num2);
	fprintf(file, "%*c", (width - shift), 'X');
	putc('\n', file);
}

void print_lines(FILE* file, int width)
{
	for (int i = 0; i < width; i++)
		fprintf(file, "-");
	putc('\n', file);
}

void print_summing(FILE* file, int num1, int num2, int width)
{
	int total_sums = count_digits(num2);
	int temp_mult;
	for (int i = 0; i < total_sums; i++)
	{
		calc_temp_mult(&temp_mult, i, num1, num2);

		fprintf(file, "%*d", width - i, temp_mult);
		putc('\n', file);
		
		if(i != (total_sums - 1))
			print_plus_symbol(file, width, i, temp_mult);
	}
}

void calc_temp_mult(int* temp_mult_var, int iteration, int num1, int num2)
{
	int multiplier = (num2 / power(CAPACITY, iteration)) % CAPACITY;
	*temp_mult_var = num1 * multiplier;
}

int power(int num, int pow)
{
	int result = 1;
	for (int i = 0; i < pow; i++)
		result *= num;
	return result;
}

void print_plus_symbol(FILE* file, int width, int iteration, int temp_mult)
{
	int shift = count_digits(temp_mult);
	fprintf(file, "%*c", (width - shift - iteration - 1), '+');
	putc('\n', file);
}

void file_opening_check(FILE* file)
{
	if (file == NULL)
	{
		puts("Failed to open the file.");
		exit(1);
	}
}