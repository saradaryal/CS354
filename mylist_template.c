#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INTS 1000
#define MAX_STRL 65535

const char *USAGE = "Usage: ./mylist <-i|-d> <OUTPUT_FILE> <FILE>...";
const char *BADFILE = "ERROR: unable to process file %s\n";
const char *LSTRECV = "LIST CONTENT AS OF FILE %s: %s\n";
const char *ORIGLST = "ORIGINAL LIST: %s\n";
const char *SORTEDLST = "SORTED LIST: %s\n";

typedef struct node {
    int data;
    struct node *next;
} node_t;

char *
list_to_string(node_t *head) {
    char *s = calloc(MAX_STRL, sizeof(char));
    if (head->next == NULL) {
        strcat(s, "Linked List is Empty.");
    } else {
        node_t *curr = head->next;
        strcat(s, "head->");
        while (curr != NULL) {
            char tempstr[12];
            sprintf(tempstr, "|%d|->", curr->data);
            strcat(s, tempstr);
            curr = curr->next;
        }
        strcat(s, "NULL");
    }
    return s;
}

void
insert(node_t *head, int data) {
    return;
}

ssize_t
build_list_from_file(node_t *head, const char *filename) {
    ssize_t numints = 0;
    return numints;
}

void
list_to_array(int *integers, node_t *head) {
    return;
}

int
qsort_inc(const void *p1, const void *p2) {
    return 0;
}

int
qsort_dec(const void *p1, const void *p2) {
    return 0;
}

void
array_to_list(node_t *head, int *integers, size_t len) {
    return;
}

int
write_to_file(const char *filename, node_t *orighead, node_t *newhead) {
    return 0;
}


int
main(int argc, char *argv[]) {
    node_t head = {.data = 0, .next = NULL};

    // Verify and process command line arguments

    // Read from files and generate a list

    // Convert the list to an array

    // Sort the array

    // Convert the sorted array to a new list

    // Write both lists to an output file

    return 0;
}
