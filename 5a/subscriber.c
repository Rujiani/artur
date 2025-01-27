#include "subscriber.h"
#include <stdio.h>
#include <string.h>

void sub_print(const Sub *s) {
    // Print subscriber in a formatted manner
    printf("{Name: %s, Number: %s, Time: %d}",
           s->full_name ? s->full_name : "(null)",
           s->number ? s->number : "(null)",
           s->last_call_time);
}

// Compare subscribers by full_name ascending
int sub_cmp_full_name_asc(const Sub *s1, const Sub *s2) {
    return strcmp(s1->full_name, s2->full_name);
}

// Compare subscribers by full_name descending
int sub_cmp_full_name_desc(const Sub *s1, const Sub *s2) {
    return strcmp(s2->full_name, s1->full_name);
}

// Compare subscribers by number ascending
int sub_cmp_number_asc(const Sub *s1, const Sub *s2) {
    return strcmp(s1->number, s2->number);
}

// Compare subscribers by number descending
int sub_cmp_number_desc(const Sub *s1, const Sub *s2) {
    return strcmp(s2->number, s1->number);
}

// Compare subscribers by last_call_time ascending
int sub_cmp_last_call_time_asc(const Sub *s1, const Sub *s2) {
    return s1->last_call_time - s2->last_call_time;
}

// Compare subscribers by last_call_time descending
int sub_cmp_last_call_time_desc(const Sub *s1, const Sub *s2) {
    return s2->last_call_time - s1->last_call_time;
}
