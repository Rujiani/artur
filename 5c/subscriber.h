#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

typedef struct subscriber {
    char *full_name;     // dynamically allocated
    char *number;        // dynamically allocated
    int last_call_time;
} Sub;

// Free dynamic fields of one subscriber
void sub_free(Sub *s);

#endif
