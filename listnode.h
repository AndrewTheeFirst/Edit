#pragma once

struct LN typedef ListNode;

// initlaizes a new ListNode list
ListNode* new_list(void);

// frees a node list
void destroy_list(ListNode* head);

// push text on to the end of the list
int push(ListNode* head, const char* text);

// pop off text at end of the list
int pop(ListNode* head);

// insert text at given line number
int add(ListNode* head, int line_index, char* text);

// remove a range of line numbers from list (inclusive start, exclusive stop)
int drop(ListNode* head, int start, int stop);

// edit text at given line number
int edit(ListNode* head, int line_index, char* text);

// return string stored at a given line number
char* get_line(ListNode* head, int line_index);

// return the size of a list
int length(ListNode* head);

// print all lines in a list
int print(ListNode* head);

// print a range of line numbers from list (inclusive start, exclusive stop)
int print_range(ListNode* head, int start, int stop);