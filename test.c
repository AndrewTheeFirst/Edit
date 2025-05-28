#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linenode.h"

int main() {
    LineNode* doc = init_LN("Line 0: Well");
    append(doc, "Line 1: Hello");
    append(doc, "Line 2: World");
    append(doc, "Line 3: Foo");
    append(doc, "Line 4: Bar");
    append(doc, "Line 5: Baz");

    printf("\nFull document:\n");
    print_all(doc);

    printf("\nInserting line at position 3...\n");
    add(doc, 3, "Line 3.5: Inserted");

    printf("\nDocument after insertion:\n");
    print_all(doc);

    printf("\nEditing line 2...\n");
    edit(doc, 2, "Line 2: Edited World");

    printf("\nDocument after edit:\n");
    print_all(doc);

    printf("\nPrinting lines 2 to 5 (exclusive of 5):\n");
    print_lines(doc, 2, 5);  // lines 2,3,4

    printf("\nDropping lines 1 to 3 (exclusive of 3)...\n");
    drop(doc, 1, 3);  // removes line 1 and 2

    printf("\nDocument after drop:\n");
    print_all(doc);

    // printf("\nCleaning up memory...\n");

    // printf("Done.\n");
    return 0;
}