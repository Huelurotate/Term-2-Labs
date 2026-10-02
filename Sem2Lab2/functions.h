#define EXTENSION_LEN 4
#define WRITE_CHOICE 1
#define APPEND_CHOICE 0
#define NEED_NEW_FILENAME 1
#define NEED_FILENAME 0 
#define CAPACITY 10

// Initial filename
void create_filename(char** filename_var, int* file_exist, int new_filename_flag);
void filename_input(char** str, int* length);
void str_input(char** str, int* length);
void check_char_alloc(char* memory_block);
void check_file_exist(char* filename_var, int* flag);
void print_message(int file_exist);

// Menu
void menu(char* filename, int file_exist);
void print_menu();
void menu_option_choice(int* choice);

// Input and related
void file_input(char* filename, int* has_numbers, int file_exist);
void manual_file_input(char* filename, int* has_numbers, int user_input_choice);

void select_file_open_mode(FILE** file, char* filename_var, int* has_numbers, int user_input_var);

// Loops
void input_mode_choice(int* choice);
void choice_loop(int* choice_var);
void int_input_loop(int* var);

// Output
void output_file(char* filename);

// Printing even numbers
void print_file_even(char* filename);

// Multiplication algorithm
void multiply_two_file_numbers(char* main_filename);

void get_two_file_numbers(char* filename, int* var1, int* var2, int* flag);
void get_file_number(FILE* file_var, int* var, int* flag);

void find_width(int* total_width, int num1, int num2);
int count_digits(int num);

void print_multiplication(char* filename, int num1, int num2, int width);

void print_two_numbers(FILE* file, int num1, int num2, int width);
void print_number(FILE* file, int number, int width);
void print_mult_symbol(FILE* file, int width, int num1, int num2);

void print_lines(FILE* file, int width);

void print_summing(FILE* file, int num1, int num2, int width);
void calc_temp_mult(int* temp_mult_var, int iteration, int num1, int num2);
int power(int num, int pow);
void print_plus_symbol(FILE* file, int width, int iteration, int temp_mult);

// File opening check
void file_opening_check(FILE* file);