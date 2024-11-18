#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <ctype.h>

int validate_int(const char *message) {
  int num;
  printf("%s", message);
  while (scanf(" %d", &num) != 1) {
    while (getchar() != '\n') {};
    printf("Invalid input, please enter an integer: ");
  }
  while (getchar() != '\n') {};
  return num;
}

double validate_double(const char *message) {
  double num;
  printf("%s", message);
  while (scanf(" %lf", &num) != 1) {
    while (getchar() != '\n')
      ;
    printf("Invalid input, please enter a double: ");
  }
  return num;
}

char *validate_string(const char *message, int bufferSize) {
  char *buffer = malloc(bufferSize * sizeof(char));
  if (buffer == NULL) {
    printf("Failed to allocate memory.\n");
    return NULL;
  }
  printf("%s", message);
  if (fgets(buffer, bufferSize, stdin) != NULL) {
    // Remove trailing newline
    buffer[strcspn(buffer, "\n")] = 0;
  } else {
    printf("Error reading input.\n");
    free(buffer);
    return NULL;
  }
  title_case(buffer);
  return buffer;
}

void title_case(char *str) {
  // Use this with ctype.h
  // *str = toupper(*(str));
  // for (int i = 1; *(str + i) != '\0'; ++i) {
  //   if (*(str + i) == ' ') {
  //     *(str + i + 1) = toupper(*(str + i + 1));
  //     ++i;
  //   }
  // }
  *str = (*str >= 97) ? (*str - 32) : (*str);
  for (int i = 1; *(str + i) != '\0'; ++i) {
    if (*(str + i) == ' ') {
      char *current = str + i++ + 1;
      *current = (*current >= 97) ? (*current - 32) :(*current);
    }
  }
}
