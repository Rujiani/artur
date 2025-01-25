#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int add_Element(Node **head, char c) {
    while (*head)
        head = &(*head)->next;
    *head = malloc(sizeof(Node));
    if (!*head) return 1;
    (*head)->symbol = c;
    (*head)->next = NULL;
    return 0;
}

int delete_Element(Node **head) {
    if (!*head) return 0;
    Node *p = *head;
    *head = p->next;
    free(p);
    return 0;
}

void print_List(Node *head) {
    putchar('"');
    while (head) {
        putchar(head->symbol);
        head = head->next;
    }
    putchar('"');
    putchar('\n');
}

void free_List(Node **head) {
    while (*head) {
        Node *p = *head;
        *head = p->next;
        free(p);
    }
}

int input_List(Node **head) {
    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (add_Element(head, (char)c)) return 1;
    }
    if (c == EOF) return 0;
    return -1;
}

int break_The_Words(Node **src, Node **dst, int N) {
    Node *p = *src;
    int firstOutputWord = 1;
    while (p) {
        while (p && (p->symbol == ' ' || p->symbol == '\t'))
            p = p->next;
        if (!p) break;
        int wordLen = 0;
        Node *start = p;
        while (p && (p->symbol != ' ' && p->symbol != '\t')) {
            wordLen++;
            p = p->next;
        }
        Node *q = start;
        int processed = 0;
        while (processed < wordLen) {
            int chunkSize = (wordLen - processed > N) ? N : (wordLen - processed);
            if (!firstOutputWord) {
                if (add_Element(dst, ' ')) return 1;
            }
            for (int i = 0; i < chunkSize; i++) {
                if (add_Element(dst, q->symbol)) return 1;
                q = q->next;
            }
            processed += chunkSize;
            firstOutputWord = 0;
        }
    }
    return 0;
}
