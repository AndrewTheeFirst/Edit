#include <stdio.h>
#include <fcntl.h> // file flags
#include <io.h> // flie functions
#include <stdlib.h>
#include <string.h>
#include "listnode.h"

#define BUFFSIZE 32

// returns a char* of text up to \n or end of string
char* _get_line(const char* string);

// counts # words seperated by spaces
int _count_words(char* string);

char* get_file_text(const char* filename){
    int file_desc = open(filename, O_RDONLY);
    if (file_desc < 0){
        return NULL;
    }
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
    close(file_desc);
    text_head_ptr[total_bytes_read] = '\0';
    return text_head_ptr;
}

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

char* strip_r_newline(char* string){
    int string_len = strlen(string);
    char* stripped_string;
    int stripped_len;
    for (int index = string_len - 1; index >= 0; index--){
        if (string[index] != '\n'){
            stripped_len = index + 1;
            stripped_string = (char*)malloc(stripped_len + 1); // + 1 for \0
            memcpy(stripped_string, string, stripped_len);
            stripped_string[stripped_len] = '\0';
            return stripped_string;
        }
    }
    return "";
}

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

int _count_words(char* string){
    int num_words = 0;
    while (1){
        // skip any spaces
        while (string[0] == ' '){
            string++;
        }

        // end of string
        if (string[0] == '\0'){
            break;
        }

        //skip any chars
        while (!(string[0] == ' ' || string[0] == '\0')){
            string++;
        }
        num_words++;
    }
    return num_words;
}

char** split_string(char* string){
    char** word_list;
    int num_words = _count_words(string);
    int num_letters;
    word_list = (char**)malloc(sizeof(char*) * (num_words + 1)); // + 1 for NULL pointer (acts as terminator)
    char* word = string;

    for (int index = 0; index < num_words; index++){
        // skip any spaces
        while (string[0] == ' '){
            string++;
        }
        
        // end of string
        if (string[0] == '\0'){
            break;
        }
        // mark beginning of the word and count letters
        word = string;
        num_letters = 0;
        while (!(string[0] == ' ' || string[0] == '\0')){
            string++;
            num_letters++;
        }
        word_list[index] = (char*)malloc(num_letters + 1);
        memcpy(word_list[index], word, num_letters);
        word_list[index][num_letters] = '\0';
    }
    word_list[num_words] = NULL;
    return word_list;
}

char* get_trail(char* string, int num_skips){
    char* trail;
    int num_words = _count_words(string);

    if (num_skips >= num_words){
        return NULL;
    }
    while (num_skips > 0){
        // skip any spaces
        while (string[0] == ' '){
            string++;
        }
        // skip word
        while (string[0] != ' '){
            string++;
        }
        num_skips--;
    }
    // skip any spaces
    while (string[0] == ' '){
        string++;
    }
    int len_trail = strlen(string);
    trail = (char*)malloc(len_trail + 1);
    strcpy(trail, string);
    return trail;
}

ListNode* strings_to_list(char** strings){
    ListNode* list = new_list();
    while (strings[0] != NULL){
        push(list, strings[0]);
        strings++;
    }
    return list;
}

int is_digit(char* string){
    int digit_flag = 1;
    unsigned char ascii_val;
    for (int index = 0; index < strlen(string); index++){
        ascii_val = (int)string[index];
        if (!((47 < ascii_val && ascii_val < 58) || ascii_val == 45)){ // NOTE: #'s 0-9 are vals 48-57 in ascii. 45 is -
            digit_flag = 0;
        }
    }
    return digit_flag;
}