#ifndef LIST_H_
#define LIST_H_

typedef struct node{
    char symbol;
    struct node *next;
} Node;

int input_List(Node **);
int add_Element(Node **, char);
int delete_Element(Node **);
void print_List(Node *);
void free_List(Node **);
int break_The_Words(Node **, Node **, int); 

#endif