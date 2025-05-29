#include <stdio.h> // printf, fgets, stdin
#include <stdlib.h> // malloc, free
#include <string.h> // memcpy, strcpy, strcmp
#include <io.h>
#include "tools.h"
#include "fcntl.h"

#define MAX_LINE_LEN 128

int take_command(void);
int manage_list(ListNode* list);

int main(void){
    while (take_command()){}
    return 0;
}

int take_command(void){
    printf("USER > ");
    char buffer[MAX_LINE_LEN];
    fgets(buffer, MAX_LINE_LEN - 1, stdin);
    char** argv = split_string(buffer);
    ListNode* arg_list = strings_to_list(argv);
    int argc = length(arg_list);
    char* command = strip_r_newline(get_line(arg_list, 0));
    if (strcmp(command, "QUIT") == 0){ // ie. QUIT\n
        return 0;
    }
    else if (strcmp(command, "OPEN") == 0 && argc == 2){ // ie. OPEN insert_filename.txt\n
        char* filename = strip_r_newline(get_line(arg_list, 1));
        char* file_text = get_file_text(filename);
        if (file_text){ // if file opened properly
            ListNode* text_list = string_to_list(file_text);
            while(manage_list(text_list)){}
        }
        else{
            printf("Open Command Failed.\n");
        }
    }
    else{
        printf("Command Failed.\n");
    }
    return 1;
}

int manage_list(ListNode* list){
    printf("\nUSER/EDIT > ");
    char buffer[MAX_LINE_LEN];
    fgets(buffer, MAX_LINE_LEN - 1, stdin);
    char** argv = split_string(buffer);
    ListNode* arg_list = strings_to_list(argv);
    int argc = length(arg_list);
    char* command = strip_r_newline(get_line(arg_list, 0));
    
    if (strcmp(command, "QUIT") == 0 && argc == 1){ // ie. QUIT\n
        return 0;
    }
    else if (strcmp(command, "LIST") == 0 && (argc == 3 || argc == 1)){ // ie. LIST 4 8\n ; LIST\n
        if (argc == 1){
            print(list);
        }
        else{
            char* start = get_line(arg_list, 1);
            char* stop = strip_r_newline(get_line(arg_list, 2));
            if (is_digit(start) && is_digit(stop)){
                print_range(list, atoi(start), atoi(stop));
            }
            else{
                printf("Command Failed.\n");
            }
        }
    }
    else if (strcmp(command, "EDIT") == 0 && argc >= 3){ // ie. EDIT 4 InsertText\n
        char* line_number = strip_r_newline(get_line(arg_list, 1));
        char* text = get_trail(buffer, 2);
        if (is_digit(line_number)){
            edit(list, atoi(line_number), text);
        }
        else{
            printf("Command Failed.\n");
        }
    }
    else if (strcmp(command, "DROP") == 0 && argc == 3){ // ie. DROP 3 6\n
        char* start = get_line(arg_list, 1);
        char* stop = strip_r_newline(get_line(arg_list, 2));
        if (is_digit(start) && is_digit(stop)){
            drop(list, atoi(start), atoi(stop));
        }
        else{
            printf("Command Failed.\n");
        }
    }
    else if (strcmp(command, "ADD<") == 0 && argc >= 3){ // ADD< 8 InsertText\n
        char* line_number = strip_r_newline(get_line(arg_list, 1));
        char* text = get_trail(buffer, 2);
        if (is_digit(line_number)){
            add(list, atoi(line_number), text);
        }
        else{
            printf("Command Failed.\n");
        }
    }
    else if (strcmp(command, "@END") == 0 && argc >= 2){ // @END InsertText\n
        char* text = get_trail(buffer, 1);
        push(list, text);
    }
    else{
        printf("Command Failed.\n");
    }

    return 1;
}