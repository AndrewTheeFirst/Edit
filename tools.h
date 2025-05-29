#include "listnode.h"

// opens a txt file and extracts it into a char*
char* get_file_text(const char* filename);

// loads char* into a listnode (split by \n)
ListNode* string_to_list(char* text);

// returns a list containing elements of a char**
ListNode* strings_to_list(char** strings);

// returns a char** of a given string split on spaces
char** split_string(char* string);

// creates a copy of strings contents but without trailing \n
char* strip_r_newline(char* string);

// returns 1 or 0 if a char* is numerical respectively
int is_digit(char* string);

// return a char* of trailing string after given # of words to skip
char* get_trail(char* string, int num_skips);