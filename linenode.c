#include "linenode.h"
#include <stdio.h>
#include <stdlib.h> // contains free, malloc, 
#include <string.h> // contains strcpy, memcpy

#define ERROR 1
#define SUCCESS 0

int change_node_text(LineNode* head, const char* text);
int __free_node(LineNode* head);

// NOTE: line numbers are 0-indexed

// automatically free and allocate for char* in node
int change_node_text(LineNode* head, const char* text){
    if (head->text){
        free(head->text);
        head->text = NULL;
    }
    head->text = (char*)malloc(strlen(text) + 1);
    strcpy(head->text, text);
    return SUCCESS;
}

// frees an individual node
int __free_node(LineNode* head){
    free(head->text); // memory was allocated for char* so we must free it
    head->text = NULL; // not necessary, but safe
    head->next = NULL;
    free(head); // free up node itself
    return SUCCESS;
}

// initlaizes a text node
LineNode* init_LN(const char* text){
    LineNode* head = (LineNode*)malloc(sizeof(LineNode));
    head->next = NULL;
    head->text = NULL;
    change_node_text(head, text);
    return head;
}

// frees the linked list associated with the node
int free_node(LineNode* head){
    if (head && head->next) {
        free_node(head->next);
    }
    __free_node(head);
    return SUCCESS;
}

// insert text at given line number
int add(LineNode* head, int line_num, char* text){
    int num_lines = length(head);
    if (line_num > num_lines || line_num < 0){ // past back of last or in front of first
        return ERROR;
    }
    else {
        // move head to target node
        for (int index = 0; index < line_num; index++){
            head = head->next;
        }
        // create new middle node
        LineNode* new_node = init_LN(head->text);
        new_node->next = head->next;

        // update target
        head->next = new_node;
        change_node_text(head, text);
    }
    return SUCCESS;
}

// push text on to the end of the list
int append(LineNode* head, char* text){
    while (head->next != NULL){
        head = head->next;
    }
    head->next = init_LN(text);
    return SUCCESS;
}

// remove a range of line numbers from list (inclusive start, exclusive stop)
int drop(LineNode* head, int start, int stop){
    // lets assume an exclusive stop (ie. start: 2, stop: 5 -> [2, 3, 4])
    int num_lines = length(head);
    if (start < 0 || stop > num_lines || stop <= start){
        return ERROR;
    }

    // move to head to node right before start (if possible) so head may be re-assigned
    for (int index = 0; index < start - 1; index++) {
        head = head->next;
    }
    
    LineNode* next_node = head->next;
    LineNode* current_node;
    // deletes (stop - start) nodes starting at next_node
    if (start == 0){
        for(int index = start; index < stop - 1; index++) {
            current_node = next_node;
            next_node = current_node->next;
            __free_node(current_node);
        }
        change_node_text(head, next_node->text);
        head->next = next_node->next;
        __free_node(next_node);
    }
    else{
        for(int index = start; index < stop; index++) {
            current_node = next_node;
            next_node = current_node->next;
            __free_node(current_node);
        }
        head->next = next_node;
    }
    return SUCCESS;
}

int edit(LineNode* head, int line_num, char* text){
    for (int index = 0; index < line_num; index++) {
        head = head->next;
    }
    change_node_text(head, text);
    return SUCCESS;
}

// print a range of line numbers from list (inclusive start, exclusive stop)
int print_lines(LineNode* head, int start, int stop){
    int num_lines = length(head);
    if (start < 0 || stop > num_lines || stop <= start){
        return ERROR;
    }

    // move to target
    for (int index = 0; index < start; index++) {
        head = head->next;
    }

    // print (stop - start) lines
    for (int index = start; index < stop; index++) {
        printf("%s\n", head->text);
        head = head->next;
    }
    return SUCCESS;
}

// print all lines in a list
int print_all(LineNode* head){
    while(head != NULL){
        printf("%s\n", head->text);
        head = head->next;
    }
    return SUCCESS;
}

// return the size of a list
int length(LineNode* head){
    int size = 0;
    while (head != NULL){
        size++;
        head = head->next;
    }
    return size;
}