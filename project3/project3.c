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

   // allocate node
    node_t *first_node = malloc(sizeof(node_t)); 
    // put in the data 
    first_node->data  = data; 
   
    // Make next of new node as head 
    first_node->next = head; 
   
    // move the head to point to the new node 
    head = first_node; 
    //printf("DATA INSERTED SUCCESSFULLY\n");
} 
    

ssize_t build_list_from_file(node_t *head, const char *filename) {
    ssize_t numints = 0;
    FILE *fp;
    char line[MAX_INTS];
    fp = fopen(filename, "r");
    if(!fp){
        printf("%s", BADFILE);
        return -1;
    }
    while(fgets(line, MAX_INTS, fp) != 0){
        insert(head, atoi(line));
        numints ++;
   }
    fclose(fp);
   printf("%d", numints);
   return numints;
}

void
list_to_array(int *integers, node_t *head) {
   int i = 0;
   node_t *curr =head;
   // Traverse the Linked List and add the
    // elements to the array one by one
    while (curr != NULL) {
        integers[i++] = curr->data;
        curr = curr->next;
    }
 }


int
qsort_inc(const void *p1, const void *p2) {
    return ( *(int*)p1 - *(int*)p2 );
}

int
qsort_dec(const void *p1, const void *p2) {
    return ( *(int*)p2 - *(int*)p1);
}

void
array_to_list(node_t *head, int *integers, size_t len) {
    
    for (int i = 0; i < len; i++){
        insert(head, integers[i]);
    }
}

int
write_to_file(const char *filename, node_t *orighead, node_t *newhead) {
    FILE *pfile = fopen(filename, "w");
    char *orig = list_to_string(orighead);
    char *new = list_to_string(newhead);
    if (pfile != NULL) {
        for (; orighead != NULL; orighead = orighead->next) {
            fprintf(pfile, "%s %s", ORIGLST, orig);
            return 0;
          }
    
        for (; newhead != NULL; newhead = newhead->next) {
            fprintf(pfile, "%s %s" , SORTEDLST, new);
            return 0;
           }
        }else {
            return -1;
        }
    fclose(pfile);
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

    //check if the user input is correct
    if (argc < 4){
         printf(USAGE, argv[0]);
        exit(1);
        }

    if((strcmp(argv[1], "i") != 0) || (strcmp(argv[1], "d")) != 0){
        printf(USAGE, argv[0]);
        exit(1);
    }
        // point output to the output file
    char *output = argv[2];
    // build list from the file provided by the user in argv[3] and upwards
    for (int i = 3; i < argc; i++){
        ssize_t arr = build_list_from_file(&head, argv[i]);  
        int array[MAX_INTS];
        list_to_array(array, &head);
        int result = strcmp(argv[1], "i");
            if((result = 0)){ 
                qsort(array, arr, sizeof(int), qsort_inc);
            }else{
                qsort(array, arr, sizeof(int), qsort_dec); 
            }
            
            node_t tail = {.data = 0, .next = NULL};
            array_to_list(&tail, array, arr);
            write_to_file(output, &head, &tail);
    }
    return 0;
}
