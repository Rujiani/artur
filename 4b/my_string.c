#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>

static int is_delim(char c, const char *delim) {
    while (*delim) {
        if (*delim++ == c) return 1;
    }
    return 0;
}

unsigned long my_strlen(const char *str) {
    unsigned long len = 0;
    while (str[len]) len++;
    return len;
}

char *my_strcat(char *dest, const char *src) {
    char *d = dest;
    while (*d) d++;
    while (*src) {
        *d++ = *src++;
    }
    *d = '\0';
    return dest;
}

char *my_strtok(char *str, const char *delim) {
    static char *saved = NULL;
    if (str) saved = str;
    if (!saved) return NULL;

    while (*saved && is_delim(*saved, delim)) saved++;
    if (!*saved) {
        saved = NULL;
        return NULL;
    }

    char *token_start = saved;
    while (*saved && !is_delim(*saved, delim)) saved++;
    if (*saved) {
        *saved++ = '\0';
    } else {
        saved = NULL;
    }
    return token_start;
}

char *my_readline(const char *prompt) {
    if (prompt) {
        fputs(prompt, stdout);
        fflush(stdout);
    }
    size_t cap = 128, len = 0;
    char *buf = (char*)malloc(cap);
    if (!buf) return NULL;

    int c;
    while ((c = fgetc(stdin)) != EOF && c != '\n') {
        buf[len++] = (char)c;
        if (len + 1 >= cap) {
            cap *= 2;
            char *new_buf = (char*)realloc(buf, cap);
            if (!new_buf) {
                free(buf);
                return NULL;
            }
            buf = new_buf;
        }
    }
    if (len == 0 && c == EOF) {
        free(buf);
        return NULL;
    }
    buf[len] = '\0';
    return buf;
}
