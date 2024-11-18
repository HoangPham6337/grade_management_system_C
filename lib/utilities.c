// Copyright 2024 <Pham Xuan Hoang>
#include "utilities.h"
#include <stdlib.h>

void freeList(List *courseList) {
  if (courseList == NULL) {
    return;
  }
  Course *current = courseList->pHead;
  while (current != NULL) {
    Course *next = current->pNext;
    free(current);
    current = next;
  }
  free(current);
  free(courseList);
}

void clearScreen() {
  #ifdef _WIN32
    system("cls");
  #else //__linux__
    system("clear");
  #endif
}
