#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void menu(Bank_Info* struct_arr)
{
	int menu_choice, is_running = 1;
	int total_accounts = 0;

	while (is_running)
	{
		print_menu();
		menu_option_choice(&menu_choice);
		switch (menu_choice)
		{
		case 1:
			input_bank_info(&struct_arr, &total_accounts);
			break;
		case 2:
			if (total_accounts > 0)
				output_bank_info(struct_arr, total_accounts);
			else
				puts("\nThere are no accounts.");
			break;
		case 3:
			if (total_accounts > 0)
				find_max_dep_val(struct_arr, total_accounts);
			else
				puts("\nThere are no accounts.");
			break;
		case 4:
			if (total_accounts > 0)
				delete_accounts(&struct_arr, &total_accounts);
			else
				puts("\nThere are no accounts.");
			break;
		case 5:
			free_struct_array(&struct_arr, &total_accounts);
			is_running = 0;
			break;
		}
	}
}

void print_menu()
{
	puts("\n      MENU\n"
		"Choose an option:\n"
		"1 - Input Clients' Accounts\n"
		"2 - Output Clients' Accounts\n"
		"3 - Find Biggest Deposit Value\n"
		"4 - Delete Client's Accounts\n"
		"5 - Exit Program");
}

void menu_option_choice(int* choice)
{
	while (1)
	{
		int_input(choice);
		if (*choice < 1 || *choice > 5)
			puts("\nChoose an option(1-5).");
		else
			break;
	}
}

void input_bank_info(Bank_Info** struct_arr, int* total_accounts)
{
	int continue_choice = 0;

	if (*total_accounts > 0)
		struct_rewrite_request(struct_arr, total_accounts);

	do
	{
		*struct_arr = realloc(*struct_arr, sizeof(Bank_Info) * (*total_accounts + 1));
		struct_alloc_check(*struct_arr);

		input_passport_number(*struct_arr, &(*struct_arr)[*total_accounts], *total_accounts);
		input_surname(&(*struct_arr)[*total_accounts]);
		input_account_number(&(*struct_arr)[*total_accounts]);
		input_deposit_value(&(*struct_arr)[*total_accounts]);

		(*total_accounts)++;

		printf("\nInput bank info for another client?(1 - Yes, 0 - No): ");
		choice_loop(&continue_choice);
	} while (continue_choice);
}

void struct_rewrite_request(Bank_Info** struct_arr, int* total_numbers)
{
	int rewrite_choice;
	printf("\nRewrite all the bank info?(1 - Yes, 0 - No): ");
	choice_loop(&rewrite_choice);

	if (rewrite_choice)
		free_struct_array(struct_arr, total_numbers);
}

void input_passport_number(Bank_Info* struct_arr, Bank_Info* cur_struct, int total_accounts)
{
	printf("\nEnter a %d-digit passport number:\n", PASSPORT_NUM_LEN);

	while (1)
	{
		int_input(&(cur_struct->passport_number));
		if (cur_struct->passport_number < 0)
			puts("\nPassport number cannot be less than 0.");
		else if (count_digits(cur_struct->passport_number) != PASSPORT_NUM_LEN)
			puts("\nPassport number must be 9 digits long.");
		else if(check_unique_pass_num(struct_arr, total_accounts, cur_struct->passport_number))
			puts("\nThis passport number already exists.");
		else
			break;
	}
}

int check_unique_pass_num(Bank_Info* struct_arr, int total_accounts, int new_num)
{
	for (int i = 0; i < total_accounts; i++)
		if (struct_arr[i].passport_number == new_num)
			return 1;
	return 0;
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

int count_digits(int num)
{
	if (num == 0)
		return 0;

	int count = 0;
	while (num > 0)
	{
		num /= CAPACITY;
		count++;
	}
	
	return count;
}

void input_surname(Bank_Info* cur_struct)
{
	puts("\nEnter a surname:");
	cur_struct->surname = NULL;
	str_input(&cur_struct->surname);
}

void str_input(char** str)
{
	int length = 0;
	char c;

	while ((c = getchar()) == '\n')
		puts("\nYou cannot enter an empty string.");

	ungetc(c, stdin);
	while ((c = getchar()) != '\n')
	{
		length++;
		*str = realloc(*str, (length + 1) * sizeof(char));
		check_char_alloc(*str);
		(*str)[length - 1] = c;
	}

	(*str)[length] = '\0';
}

void choice_loop(int* choice_var)
{
	while (1)
	{
		int_input(choice_var);
		if (*choice_var != 1 && *choice_var != 0)
			puts("\nInvalid Input. Please, choose an option(1 or 0).");
		else
			break;
	}
}

void input_account_number(Bank_Info* cur_struct)
{
	printf("\nEnter a %d-digit account number:\n", ACC_NUM_LEN);
	get_acc_num(cur_struct->Account_Info.acc_num_and_dep_val);
}

void get_acc_num(unsigned char* var)
{
	char c;
	while (1)
	{
		fgets(var, ACC_NUM_LEN + 1, stdin);

		if (strlen(var) != ACC_NUM_LEN || var[ACC_NUM_LEN - 1] == '\n')
		{
			puts("\nInvalid Input.");
			rewind(stdin);
			continue;
		}

		if ((c = getchar()) != '\n')
		{
			puts("\nInvalid Input.");
			rewind(stdin);
			continue;
		}

		rewind(stdin);
		break;
	}
}

void input_deposit_value(Bank_Info* cur_struct)
{
	int dep_val;

	printf("\nEnter deposit value less than %d:\n", DEP_VAL_CEIL + 1);
	while (1)
	{
		int_input(&dep_val);
		if (dep_val < 0 || dep_val > DEP_VAL_CEIL)
			puts("\nInvalid Input.");
		else
			break;
	}

	switch_bits_to_num(cur_struct, dep_val);
}

void switch_bits_to_num(Bank_Info* cur_struct, int val)
{
	unsigned char cur_bit;
	for (int i = 0; i < ACC_NUM_LEN; i++)
	{
		cur_bit = (val >> (ACC_NUM_LEN - i - 1)) & 1;

		if (cur_bit)
			cur_struct->Account_Info.acc_num_and_dep_val[i] |= 0b10000000;
		else
			cur_struct->Account_Info.acc_num_and_dep_val[i] &= 0b01111111;
	}
}

void output_bank_info(Bank_Info* struct_arr, int total_accounts)
{
	unsigned char acc_num[ACC_NUM_LEN + 1];;
	unsigned short dep_val;

	for (int i = 0; i < total_accounts; i++)
	{
		printf("\nClient %d:\n", i + 1);
		printf("Passport number: %d\n", struct_arr[i].passport_number);
		printf("Surname: %s\n", struct_arr[i].surname);

		extract_acc_num(&(struct_arr[i]), acc_num);
		printf("Account number: %s\n", acc_num);
		
		extract_dep_val(&(struct_arr[i]), &dep_val);
		printf("Deposit value: %d\n", dep_val);
	}
}

void extract_acc_num(Bank_Info* cur_struct, unsigned char* var)
{
	unsigned char saved_bit;
	unsigned char* str = cur_struct->Account_Info.acc_num_and_dep_val;

	for (int i = 0; i < ACC_NUM_LEN; i++)
	{
		saved_bit = str[i] & 0b10000000;

		str[i] &= 0b01111111;
		var[i] = str[i];
		
		str[i] |= saved_bit;
	}

	var[ACC_NUM_LEN] = '\0';
}

void extract_dep_val(Bank_Info* cur_struct, short* var)
{
	*var = 0;
	unsigned char cur_bit;

	for (int i = 0; i < ACC_NUM_LEN; i++)
	{
		cur_bit = (cur_struct->Account_Info.acc_num_and_dep_val[i] >> (BITS_IN_CHAR - 1)) & 1;
		*var |= (cur_bit << (ACC_NUM_LEN - i - 1));
	}
}

void find_max_dep_val(Bank_Info* struct_arr, int total_accounts)
{
	unsigned short cur_dep_val = 0, max_dep_val = 0;

	for (int i = 0; i < total_accounts; i++)
	{
		extract_dep_val(&(struct_arr[i]), &cur_dep_val);
		if (cur_dep_val >= max_dep_val)
			max_dep_val = cur_dep_val;
	}

	printf("\nBiggest deposit value is: %d\n", max_dep_val);
}

void delete_accounts(Bank_Info** struct_arr, int* total_accounts)
{
	unsigned char target_acc_num[ACC_NUM_LEN + 1];
	printf("\nEnter a TARGET %d-digit account number:\n", ACC_NUM_LEN);
	get_acc_num(&target_acc_num);

	int is_found = 0, total = 0;
	unsigned char cur_acc_num[ACC_NUM_LEN + 1];
	for (int i = 0; i < *total_accounts; i++)
	{
		extract_acc_num(&(*struct_arr)[i], cur_acc_num);

		if (strcmp(cur_acc_num, target_acc_num) == 0)
		{
			for (int j = i; j < *total_accounts - 1; j++)
				(*struct_arr)[j] = (*struct_arr)[j + 1];

			(*total_accounts)--;
			*struct_arr = realloc(*struct_arr, sizeof(Bank_Info) * (*total_accounts));
			if(*total_accounts > 0)
				struct_alloc_check(*struct_arr);

			i--;
			is_found = 1;
			total++;
		}
	}

	if (is_found)
		printf("\nDeleted %d account(s) with %s account number.\n", total, target_acc_num);
	else
		printf("\nNo accounts with %s account number found.\n", target_acc_num);
}

void struct_alloc_check(Bank_Info* memory_block)
{
	if (memory_block == NULL)
	{
		puts("Memory allocation error.");
		exit(1);
	}
}

void check_char_alloc(char* memory_block)
{
	if (memory_block == NULL)
	{
		puts("Memory allocation error.");
		exit(1);
	}
}

void free_struct_array(Bank_Info** struct_arr, int* total_accounts)
{
	for (int i = 0; i < *total_accounts; i++)
		free((*struct_arr)[i].surname);

	free(*struct_arr);
	*struct_arr = NULL;
	*total_accounts = 0;
}