#include <stdio.h> // printf
#include <stdlib.h> // malloc, free
#include <string.h> // memcpy, strcpy
#include <stdint.h> // int types
#include "tools.h"

#define MAX_LINE_LEN 256

int main(void){
    int running = 1;
    int num_args;
    char buffer[MAX_LINE_LEN];
    char** args;
    char* command;
    ListNode* arg_list;

    while (running){
        fgets(buffer, MAX_LINE_LEN - 1, stdin);
        args = split_string(buffer);
        arg_list = strings_to_list(args);
        num_args = length(arg_list);
        command = get_line(arg_list, 0);
        if (strcmp(command, "QUIT\n") == 0){
            
        }
        else if (strcmp(command, "OPEN") == 0 && num_args == 2){

        }
        else{
            printf("Command Failed.\n");
        }
    }
    
}

// "QUIT", "LIST", "EDIT", "DROP", "ADD<", "@END"