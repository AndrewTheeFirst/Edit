#include <stdio.h> // printf, fgets, stdin, remove
#include <stdlib.h> // malloc, free
#include <string.h> // memcpy, strcpy, strcmp
#include <io.h> // open() close()
#include "fcntl.h" // file open flags
#include <sys/stat.h> // file permission flags
#include "tools.h" // listnode, various helpers

#define MAX_LINE_LEN 128

int take_command(void);
int confirm(char* prompt);
int manage_list(ListNode* list);
void free_char_ptr_ptr(char** char_ptr_ptr);

int main(void){
    while (take_command());
    return 0;
}

int take_command(void){
    printf("USER > ");
    char buffer[MAX_LINE_LEN];
    fgets(buffer, MAX_LINE_LEN - 1, stdin);
    char** argv = split_string(buffer); // heap allocated
    ListNode* arg_list = strings_to_list(argv); // heap allocated
    int argc = length(arg_list);
    char* command = strip_r_newline(get_line(arg_list, 0)); // heap allocated
    int running = 1;
    if (strcmp(command, "QUIT") == 0){ // ie. QUIT\n
        running = 0;
    }
    else if (strcmp(command, "OPEN") == 0 && argc >= 2){ // ie. OPEN insert_filename.txt\n
        char* trail = get_trail(buffer, 1); // heap allocated
        char* filename = strip_r_newline(trail); // heap allocated
        // trail no longer needed
        free(trail);
        trail = NULL;
        char* file_text = get_file_text(filename); // heap allocated
        if (file_text){ // if file opened properly
            ListNode* text_list = string_to_list(file_text); // heap allocated
            // Free file_text after use. May be large depending on the file.
            free(file_text);
            file_text = NULL;
            while(manage_list(text_list));
            char* saved_text = get_range(text_list, 0, length(text_list)); // heap allocated
            if (confirm("Save Changes to File")){
                overwrite_file(filename, saved_text);
            }
            free(saved_text);
            destroy_list(text_list);
            saved_text = NULL;
            text_list = NULL;
        }
        else{
            printf("\"%s\" Could not be opened.\n", filename);
        }
        free(filename);
        filename = NULL;
    }
    else if (strcmp(command, "NEW") == 0 && argc >= 2){ // ie. OPEN insert_filename.txt\n
        char* trail = get_trail(buffer, 1); // heap allocated
        char* filename = strip_r_newline(trail); // heap allocated
        // trail no longer needed
        free(trail);
        trail = NULL;
        // Notice: open() args are: filename, openflags, permissionflags
        // Creates a file that is open to read/written (includes deletion) within the program and is read/writeable within OS
        int file_desc = open(filename, _O_CREAT | _O_WRONLY, _S_IREAD | _S_IWRITE);
        if (file_desc > 0){
            close(file_desc);
            printf("File: \"%s\" created successfully.\n", filename);
        }
        else{
            printf("File: \"%s\" has failed to be created.\n", filename);
        }
        free(filename);
        filename = NULL;
    }
    else if (strcmp(command, "DELETE") == 0 && argc >= 2){ // ie. OPEN insert_filename.txt\n
        char* trail = get_trail(buffer, 1); // heap allocated
        char* filename = strip_r_newline(trail); // heap allocated
        // trail no longer needed
        free(trail);
        trail = NULL;
        if (confirm("Delete File")) {
            if (remove(filename) == 0){
                printf("File: \"%s\" deleted successfully.\n", filename);
            }
            else{
                printf("File: \"%s\" could not be deleted.\n", filename);
            }
        }
        free(filename);
        filename = NULL;
    }
    else{
        printf("Command Failed.\n");
    }
    free(command);
    destroy_list(arg_list);
    free_char_ptr_ptr(argv);
    command = NULL;
    arg_list = NULL;
    argv = NULL;
    return running;
}

int confirm(char* prompt){
    char buffer[MAX_LINE_LEN];
    while (1){
        printf("\n%s? (Y/N): ", prompt);
        fgets(buffer, MAX_LINE_LEN - 1, stdin);
        if (strcmp(buffer, "Y\n") == 0){
            return 1;
        }
        else if (strcmp(buffer, "N\n") == 0){
            return 0;
        }
    }
}

int manage_list(ListNode* list){
    printf("\nUSER/EDIT > ");
    char buffer[MAX_LINE_LEN];
    fgets(buffer, MAX_LINE_LEN - 1, stdin);
    char** argv = split_string(buffer); // heap allocated
    ListNode* arg_list = strings_to_list(argv); // heap allocated
    int argc = length(arg_list);
    char* command = strip_r_newline(get_line(arg_list, 0)); // heap allocated
    int running = 1;
    if (strcmp(command, "QUIT") == 0 && argc == 1){ // ie. QUIT\n
        running = 0;
    }
    else if (strcmp(command, "LIST") == 0 && (argc == 3 || argc == 1)){ // ie. LIST 4 8\n ; LIST\n
        if (argc == 1){
            print(list);
        }
        else{
            char* start = get_line(arg_list, 1);
            char* stop = strip_r_newline(get_line(arg_list, 2)); // heap allocated
            if (is_digit(start) && is_digit(stop)){
                print_range(list, atoi(start), atoi(stop));
            }
            else{
                printf("Command Failed.\n");
            }
            free(stop);
            stop = NULL;
        }
    }
    else if (strcmp(command, "EDIT") == 0 && argc >= 3){ // ie. EDIT 4 InsertText\n
        char* line_number = strip_r_newline(get_line(arg_list, 1)); // heap allocated
        char* text = get_trail(buffer, 2); // heap allocated
        if (is_digit(line_number)){
            edit(list, atoi(line_number), text);
            free(text);
            text = NULL;
        }
        else{
            printf("Command Failed.\n");
        }
        free(line_number);
        line_number = NULL;
    }
    else if (strcmp(command, "DROP") == 0 && argc == 3){ // ie. DROP 3 6\n
        char* start = get_line(arg_list, 1);
        char* stop = strip_r_newline(get_line(arg_list, 2)); // heap allocated -- done
        if (is_digit(start) && is_digit(stop)){
            drop(list, atoi(start), atoi(stop));
        }
        else{
            printf("Command Failed.\n");
        }
        free(stop);
        stop = NULL;
    }
    else if (strcmp(command, "ADD<") == 0 && argc >= 3){ // ADD< 8 InsertText\n
        char* line_number = strip_r_newline(get_line(arg_list, 1)); // heap allocated -- done
        if (is_digit(line_number)){
            char* text = get_trail(buffer, 2); // heap allocated -- done
            add(list, atoi(line_number), text);
            free(text);
            text = NULL;
        }
        else{
            printf("Command Failed.\n");
        }
        free(line_number);
        line_number = NULL;
    }
    else if (strcmp(command, "@END") == 0 && argc >= 2){ // @END InsertText\n
        char* text = get_trail(buffer, 1); // heap allocated -- done
        push(list, text);
        free(text);
        text = NULL;
    }
    else{
        printf("Command Failed.\n");
    }
    free(command);
    destroy_list(arg_list);
    free_char_ptr_ptr(argv);
    command = NULL;
    arg_list = NULL;
    argv = NULL;
    return running;
}

void free_char_ptr_ptr(char** char_ptr_ptr){
    for (int index = 0; char_ptr_ptr[index] != NULL; index++){
        free(char_ptr_ptr[index]);
        char_ptr_ptr[index] = NULL;
    }
    free(char_ptr_ptr);
}