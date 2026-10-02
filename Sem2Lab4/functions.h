#define PASSPORT_NUM_LEN 9
#define ACC_NUM_LEN 10
#define BITS_IN_CHAR 8
#define DEP_VAL_CEIL 1023
#define CAPACITY 10

typedef struct
{
	int passport_number;
	char* surname;

	union
	{
		unsigned char acc_num_and_dep_val[ACC_NUM_LEN + 1];
	} Account_Info;
} Bank_Info;

// MENU
void menu(Bank_Info* struct_arr);
void print_menu();
void menu_option_choice(int* choice);

// INPUT
void input_bank_info(Bank_Info** struct_arr, int* total_accounts);
void struct_rewrite_request(Bank_Info** struct_arr, int* total_numbers);

void input_passport_number(Bank_Info* struct_arr, Bank_Info* cur_struct, int total_accounts);
void int_input(int* var);
int count_digits(int num);

void input_surname(Bank_Info* cur_struct);
void str_input(char** str);

void input_account_number(Bank_Info* cur_struct);
void get_acc_num(unsigned char* var);

void input_deposit_value(Bank_Info* cur_struct);
void switch_bits_to_num(Bank_Info* cur_struct, int val);

void choice_loop(int* choice_var);

// OUTPUT
void output_bank_info(Bank_Info* struct_arr, int total_accounts);
void extract_dep_val(Bank_Info* cur_struct, short* var);
void extract_acc_num(Bank_Info* cur_struct, unsigned char* var);

// FIND MAX DEPOSIT VALUE
void find_max_dep_val(Bank_Info* struct_arr, int total_accounts);

// DELETE CLIENTS
void delete_accounts(Bank_Info** struct_arr, int* total_accounts);

// MEMORY ALLOCATION CHECKS AND FREEING
void struct_alloc_check(Bank_Info* memory_block);
void check_char_alloc(char* memory_block);
void free_struct_array(Bank_Info** struct_arr, int* total_accounts);