#include "gen.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Generate a random string of alpha chars
static char *random_string_alpha(int length) {
    // A-Z, a-z
    const char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alen = (int)strlen(alphabet);
    char *str = (char*)malloc(length + 1);
    for (int i = 0; i < length; i++) {
        str[i] = alphabet[rand() % alen];
    }
    str[length] = '\0';
    return str;
}

// Generate a random phone number of digits that starts with '+'
static char *random_phone_number(int length) {
    // length includes '+' sign
    // e.g. length=10 => +123456789 (9 digits + 1 plus-sign)
    // minimal length=2 => "+1"
    if (length < 2) length = 2;
    char *str = (char*)malloc(length + 1);
    str[0] = '+';
    for (int i = 1; i < length; i++) {
        str[i] = '0' + (rand() % 10); 
    }
    str[length] = '\0';
    return str;
}

Sub generate_random_sub() {
    // random lengths
    int name_len = 5 + rand() % 11;  // 5..15
    int phone_len = 3 + rand() % 10; // 3..12 (so + plus ~ 2..11 digits)
    Sub s;
    s.full_name = random_string_alpha(name_len);
    s.number = random_phone_number(phone_len);

    // random time in some range
    s.last_call_time = 1600000000 + rand() % 200000000; 
    return s;
}

Sub* generate_sub_array(int size) {
    if (size <= 0) return NULL;
    Sub *arr = (Sub*)malloc(size * sizeof(Sub));
    for (int i = 0; i < size; i++) {
        arr[i] = generate_random_sub();
    }
    return arr;
}

void free_sub_array(Sub *arr, int size) {
    if (!arr) return;
    for (int i = 0; i < size; i++) {
        sub_free(&arr[i]);
    }
    free(arr);
}
