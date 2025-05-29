#include "listnode.h"

char* txt_to_string(const char* filename);
ListNode* string_to_list(char* text);
ListNode* strings_to_list(char** strings);
char** split_string(char* string);