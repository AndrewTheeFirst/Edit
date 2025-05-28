#include <stdio.h>
#include "listnode.h"

int test_suite(void) {
    
    ListNode* list = new_list();
    printf("\nPopulating List:\n");
    push(list, "This is test\n");
    push(list, "And another one\n");
    push(list, "And this is the last one\n");
    push(list, "Okay okay. Not really.\n");
    printf("\noriginal_list:\n");
    print(list);
    
    printf("\ntesting print_range:\n");
    print_range(list, 0, 1);
    printf("\n");
    print_range(list, 0, 4);
    printf("\n");
    print_range(list, 1, 3);
    printf("\n");
    print_range(list, 3, 3);
    printf("\n");
    print_range(list, 3, 4);

    printf("\nList before popping:\n");
    print(list);

    printf("\nList after pop #1:\n");
    pop(list);
    print(list);
    printf("\n");

    printf("\nList after pop #2:\n");
    pop(list);
    print(list);
    printf("\n");

    printf("\nList after pop #3:\n");
    pop(list);
    print(list);

    printf("\nList after pop #4:\n");
    pop(list);
    print(list);

    printf("\nPopulating List:\n");
    push(list, "This is test\n");
    push(list, "And another one\n");
    push(list, "And this is the last one\n");
    push(list, "Okay okay. Not really.\n");
    print(list);

    printf("\nAdding more lines:\n");
    add(list, 0, "Adding at line #0\n");
    print(list);

    printf("\nAdding more lines:\n");
    add(list, 3, "Adding at line #3\n");
    print(list);

    printf("\nAdding more lines:\n");
    add(list, 5, "Adding at line #5\n");
    print(list);

    printf("\nMaking changes:\n");
    edit(list, 0, "I edited this one..\n");
    edit(list, 3, "..This one..,\n");
    edit(list, 5, "And this one.\n");
    print(list);

    printf("\nDropping lines 3-5\n");
    drop(list, 3, 6);
    print(list);

    printf("\nDropping lines 2 and 3\n");
    drop(list, 2, 4);
    print(list);

    printf("\nDropping lines 0 and 1\n");
    drop(list, 0, 2);
    print(list);

    printf("\nPopulating List:\n");
    push(list, "This is test\n");
    push(list, "And another one\n");
    push(list, "And this is the last one\n");
    push(list, "Okay okay. Not really.\n");
    print(list);

    printf("\nDeleting List:\n");
    destroy_list(list);
    return 0;
    // printf("Testing %s:\n", "destroy_list()");
    // printf("Testing %s:\n", "drop()");
}