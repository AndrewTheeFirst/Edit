#include "listnode.h"
#include <stdio.h> // used for prinf
#include <stdlib.h> // used for free, malloc, 
#include <string.h> // used for strcpy, memcpy

#define ERROR 0x1
#define SUCCESS 0x0

// sentinel-style linked list
struct LN{
    char* text;
    struct LN* next;
    struct LN* head;
    struct LN* tail;
} typedef ListNode;

// initlaizes a new child node
ListNode* _create_node(ListNode* parent, const char* text);

// frees an individual node
void _destroy_node(ListNode* node);

// automatically free and allocate for char* in node
int _change_node_text(ListNode* head, const char* text);

ListNode* _create_node(ListNode* parent, const char* text){
    ListNode* child = (ListNode*)malloc(sizeof(ListNode));
    child->head = parent->head;
    child->tail = parent->tail;
    child->next = parent->tail;
    child->text = NULL;
    _change_node_text(child, text);
    return child;
}

void _destroy_node(ListNode* node){
    if (node != node->head && node != node->tail){
        free(node->text);
    }
    free(node);
}

int _change_node_text(ListNode* node, const char* text){
    if (node->text){
        free(node->text);
        node->text = NULL;
    }
    node->text = (char*)malloc(strlen(text) + 1);
    strcpy(node->text, text);
    return SUCCESS;
}

ListNode* new_list(void){
    ListNode* tail = (ListNode*) malloc(sizeof(ListNode));
    tail->tail = tail;
    tail->next = NULL;
    tail->text = "";

    ListNode* head = (ListNode*) malloc(sizeof(ListNode));
    head->head = head;
    head->tail = tail;
    head->next = tail;
    head->text = "";
    
    tail->head = head;
    return head;
}

void destroy_list(ListNode* head){
    if (head == NULL){
        return;
    }
    destroy_list(head->next);
    _destroy_node(head);
}

int push(ListNode* head, const char* text){
    if (head == NULL || 
        head != head->head){ // enforce correct use
        return ERROR;
    }
    while (head->next != head->tail){
        head = head->next;
    }
    ListNode* new_node = _create_node(head, text);
    head->next = new_node;
    return SUCCESS;
}

int pop(ListNode* head){
    if (head == NULL || 
        head != head->head){ // enforce correct use
        return ERROR;
    }
    if (head->next == head->tail){
        return SUCCESS;
    }
    while (head->next->next != head->tail){
        head = head->next;
    }
    _destroy_node(head->next);
    head->next = head->tail;
    if (head->next == head->tail){
        return SUCCESS;
    }
}

int add(ListNode* head, int line_index, char* text){
    if (head == NULL || 
        head != head->head){
        return ERROR;
    }
    int num_lines = length(head);
    if (line_index > num_lines || line_index < 0){ // past back of last or in front of first
        return ERROR;
    }

    // move head to target node
    for (int index = 0; index < line_index; index++){
        head = head->next;
    }

    // create new node to insert
    ListNode* new_node = _create_node(head, text);
    ListNode* following_node = head->next;

    // update pointers
    head->next = new_node;
    new_node->next = following_node;
    return SUCCESS;
}

int drop(ListNode* head, int start, int stop){
    if (head == NULL || 
        head != head->head){ // enforce correct use
        return ERROR;
    }
    int num_lines = length(head);
    if (start < 0 || stop > num_lines || stop <= start){ // bounds check
        return ERROR;
    }
    
    // traverse to node before starting node
    for (int index = 0; index < start; index++){
        head = head->next;
    }
    ListNode* current_node = head->next;
    ListNode* temp;
    // delete nodes up to stop node
    for (int index = start; index < stop; index++){
        temp = current_node->next;
        _destroy_node(current_node);
        current_node = temp;
    }
    head->next = current_node;
    return SUCCESS;
}

int edit(ListNode* head, int line_index, char* text){
    if (head == NULL || 
        head != head->head){
        return ERROR;
    }
    int num_lines = length(head);
    if (line_index > num_lines || line_index < 0){ // out of bounds check
        return ERROR;
    }
    head = head->next;
    while (line_index != 0){
        head = head->next;
        line_index--;
    }
    _change_node_text(head, text);
    return SUCCESS;
}

char* get_line(ListNode* head, int line_index){
    if (head == NULL || 
        head != head->head){
        return NULL;
    }
    int num_lines = length(head);
    if (line_index > num_lines || line_index < 0){ // out of bounds check
        return NULL;
    }
    head = head->next;
    while (line_index != 0){
        head = head->next;
        line_index--;
    }
    return head->text;
}

int length(ListNode* head){
    int size = 0;
    while (head->next != head->tail){
        size++;
        head = head->next;
    }
    return size;
}

int print(ListNode* head){
    if (head == NULL || 
        head != head->head){
        return ERROR;
    }
    int line_number = 0;
    while (head->next != head->tail){
        head = head->next;
        printf("#%d: %s", line_number, head->text);
        line_number++;
    }
    return SUCCESS;
}

int print_range(ListNode* head, int start, int stop){
    if (head == NULL || 
        head != head->head){ // enforce correct use
        return ERROR;
    }
    int num_lines = length(head);
    if (start < 0 || stop > num_lines || stop < start){ // bound check
        return ERROR;
    }
    int line_number = 0;
    head = head->next;
    for(int index = 0; index < start; index++){
        head = head->next;
        line_number++;
    };
    for (int index = start; index < stop; index++){
        printf("#%d: %s", line_number, head->text);
        line_number++;
        head = head->next;
    }
    return SUCCESS;
}