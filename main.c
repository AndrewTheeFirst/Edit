#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "listnode.h"
#include <fcntl.h> // file flags
#include <io.h> // flie functions

#define BUFFSIZE 32

int test_suite(void);
char* txt_to_string(const char* filename);
char* _get_line(const char* string);
ListNode* string_to_list(char* text);

// opens a txt file and extracts it into a char*
char* txt_to_string(const char* filename){
    int file_desc = open(filename, O_RDONLY);
    int file_size = lseek(file_desc, 0, SEEK_END); // puts pointer to the end of file to get offset in bytes from beginning (file size)
    
    lseek(file_desc, 0, SEEK_SET); // will set the pointer to the beginning of the file (lseek should return 0)
    
    char* text_ptr = (char*) malloc(file_size + 1); // + 1 leaves space for \0
    char* text_head_ptr = text_ptr; // to keep track of beginning of text pointer
    
    int bytes_read = read(file_desc, text_ptr, BUFFSIZE);
    text_ptr += bytes_read;
    int total_bytes_read = bytes_read;

    // read data into text_ptr a little bit at a time
    while (total_bytes_read < file_size){
        bytes_read = read(file_desc, text_ptr, BUFFSIZE); // fills buffer at last filled position
        if (bytes_read <= 0){
            break;
        }
        text_ptr += bytes_read; // advance pointer
        total_bytes_read += bytes_read;
    }
    text_head_ptr[total_bytes_read] = '\0';
    return text_head_ptr;
}

// creates a char* pointing to text of string up to \n or \0. Returns \0 on empty string
char* _get_line(const char* string){
    char* line;
    const char* head = string;
    int bytes = 1; // space for \0 char
    while (string[0] != '\n' && string[0] != '\0'){
        string++; // progress pointer
        bytes++;
    }
    line = (char*)malloc(bytes);
    memcpy(line, head, bytes);
    line[bytes] = '\0';
    return line;
}

// loads char* into a listnode
ListNode* string_to_list(char* text){
    char* string;
    int len_string;
    ListNode* line_list = new_list();
    do {
        string = _get_line(text);
        len_string = strlen(string);
        push(line_list, string);
        text += len_string;
    }
    while (text[0] != '\0');

    return line_list;
}

int main(void){
    char* string = txt_to_string("../../my_text_file.txt");
    ListNode* list = string_to_list(string);
    // print(list);
    print_range(list, 39, 61);
    return 0;
}