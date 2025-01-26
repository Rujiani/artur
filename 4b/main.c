#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"

// Removes leading/trailing spaces/tabs and leaves only one space between words.
static char* preprocess(const char* s) {
  if(!s) return NULL;
  // Skip leading spaces
  while(*s && isspace((unsigned char)*s)) s++;
  // If empty now, return an empty string
  if(!*s) {
    char* r = malloc(1);
    if(r) r[0] = '\0';
    return r;
  }
  // Allocate for worst-case (no removals)
  char* tmp = malloc(my_strlen(s)+1);
  if(!tmp) return NULL;
  char* d = tmp;
  while(*s) {
    if(isspace((unsigned char)*s)) {
      // Skip extra spaces
      while(*(s+1) && isspace((unsigned char)*(s+1))) s++;
      // If next is end, don't add space
      if(!*(s+1)) break;
      *d++ = ' ';
    } else {
      *d++ = *s;
    }
    s++;
  }
  *d = '\0';
  // Remove trailing space if any
  if(d > tmp && *(d-1) == ' ') *(d-1) = '\0';
  return tmp;
}

int func(char* input, char **result) {
  if(!input || !result) return 1;
  // Preprocess string
  char *copy = preprocess(input);
  if(!copy) return 1;
  // Allocate minimal result
  *result = malloc(1);
  if(!*result) {
    free(copy);
    return 1;
  }
  (*result)[0] = '\0';
  char *token = my_strtok(copy, " ");
  int first = 1;
  while(token) {
    if(my_strlen(token) % 2 == 1) {
      size_t need = my_strlen(*result) + my_strlen(token) + 2;
      char *temp = realloc(*result, need);
      if(!temp) {
        free(copy);
        free(*result);
        return 1;
      }
      *result = temp;
      if(!first) my_strcat(*result, " "); else first = 0;
      my_strcat(*result, token);
    }
    token = my_strtok(NULL, " ");
  }
  free(copy);
  return 0;
}



void free_lines(char **one, char **two){
    if(*one){
        free(*one);
        *one = NULL;
    }
    if(*two){
        free(*two);
        *two = NULL;
    }
}

int main(){
    char *str = NULL, *result = NULL;
    while((str = my_readline("Input  string\n>  "))){
        if(func(str, &result) == 1){
            printf("Memory error!\n");
            free_lines(&str, &result);
            return 1;
        }
        printf("Input line:\n\"%s\"\n", str);
        printf("Result line:\n\"%s\"\n", result);
        free_lines(&str, &result);
    }
    free_lines(&str, &result);
    return 0;
}