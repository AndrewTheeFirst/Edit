#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linenode.h"
#include <fcntl.h> // file flags
#include <io.h> // flie functions

#define BUFFSIZE 32

char* read_file(const char* filename){
    int file_desc = open(filename, O_RDONLY);
    // lseek will return the position of the pointer in bytes relative to the bginning of the file
    int file_size = lseek(file_desc, 0, SEEK_END); // puts pointer to the end of file to get offset in bytes from beginning (file size)
    lseek(file_desc, 0, SEEK_SET); // will set the pointer to the beginning of the file (lseek should return 0)
    char* text_ptr = (char*) malloc(file_size + 1); // + 1 leaves space for \0
    char* text_head_ptr = text_ptr; // to keep track of beginning of text pointer
    int bytes_read = read(file_desc, text_ptr, BUFFSIZE);
    text_ptr += bytes_read;
    int total_bytes_read = bytes_read;
    while (total_bytes_read < file_size){
        bytes_read = read(file_desc, text_ptr, BUFFSIZE); // fills buffer at last filled position
        if (bytes_read <= 0){
            printf("total read: %d vs file size: %d\n\n", total_bytes_read, file_size);
            break;
        }
        text_ptr += bytes_read; // advance pointer
        total_bytes_read += bytes_read;
    }
    text_head_ptr[total_bytes_read] = '\0';
    return text_head_ptr;
}

int __main(void) {
    // testing init
    
    printf("\ninitializing node\n");
    LineNode* doc = init_LN("Line 0: Well...");
    printf("\nDocument after init:\n");
    print_all(doc);

    // testing append
    printf("\nAppending lines:\n");
    append(doc, "Line 1: Hello");
    append(doc, "Line 2: World");
    append(doc, "Line 3: Foo");
    append(doc, "Line 4: Bar");
    append(doc, "Line 5: Baz");
    print_all(doc);
    
    // testing add
    printf("\nInserting line at position 3...\n");
    add(doc, 3, "Line 3.5: Inserted");
    printf("\nDocument after insertion:\n");
    print_all(doc);
    
    // testing edit
    printf("\nEditing line 2...\n");
    edit(doc, 2, "Line 2: Edited World");
    printf("\nDocument after edit:\n");
    print_all(doc);

    // testing print_lines
    printf("\nPrinting lines 2 to 5 (exclusive of 5):\n");
    print_lines(doc, 2, 5);

    // testing drop
    printf("\nDropping lines 1 to 3 (exclusive of 3)...\n");
    drop(doc, 1, 3);
    printf("\nDocument after drop:\n");
    print_all(doc);

    // freeing memory
    printf("\nCleaning up memory...\n");
    free_node(doc);
    printf("\nDone.\n");

    return 0;
}