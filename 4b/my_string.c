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

char *my_strcpy(char *dest, const char *src) {
    char *d = dest;
    while ((*d++ = *src++));
    return dest;
}

char *my_readline(const char *prompt) {
    if (prompt) {
        fputs(prompt, stdout);
        fflush(stdout);
    }
    char temp[128];
    char *result = NULL;
    size_t total_len = 0;

    while (1) {
        int ret = scanf("%127[^\n]", temp); 
        if (ret == EOF) {
            if (!result) return NULL;
            break;
        }
        if (ret == 0) {
            int c = getchar(); 
            if (c == EOF && !result) return NULL;
            break;
        }
        size_t chunk_len = my_strlen(temp);
        char *new_result = realloc(result, total_len + chunk_len + 1);
        if (!new_result) {
            free(result);
            return NULL;
        }
        result = new_result;
        my_strcpy(result + total_len, temp);
        total_len += chunk_len;
        int c = getchar();
        if (c == EOF) break;
        if (c == '\n') break;
        ungetc(c, stdin);
    }
    return result;
}
