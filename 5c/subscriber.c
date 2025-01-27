#include "subscriber.h"
#include <stdlib.h>
#include <string.h>

// Comparators
int cmp_full_name_asc(const void *a, const void *b) {
    const Sub *s1 = (const Sub*)a;
    const Sub *s2 = (const Sub*)b;
    return strcmp(s1->full_name, s2->full_name);
}
int cmp_full_name_desc(const void *a, const void *b) {
    return -cmp_full_name_asc(a, b);
}
int cmp_number_asc(const void *a, const void *b) {
    const Sub *s1 = (const Sub*)a;
    const Sub *s2 = (const Sub*)b;
    return strcmp(s1->number, s2->number);
}
int cmp_number_desc(const void *a, const void *b) {
    return -cmp_number_asc(a, b);
}
int cmp_time_asc(const void *a, const void *b) {
    const Sub *s1 = (const Sub*)a;
    const Sub *s2 = (const Sub*)b;
    return (s1->last_call_time - s2->last_call_time);
}
int cmp_time_desc(const void *a, const void *b) {
    return -cmp_time_asc(a, b);
}

void sub_free(Sub *s) {
    if (!s) return;
    free(s->full_name);
    free(s->number);
    s->full_name = NULL;
    s->number = NULL;
}
