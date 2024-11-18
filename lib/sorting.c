#include "sorting.h"
#include "component.h"
#include <stdlib.h>

void swap(List *courseList, Course *a, Course *b) {
  if (a == b)
    return; // No operation needed if they're the same node.

  // Correct handling for adjacent nodes as special case
  if (a->pNext == b) { // A is directly before B
    a->pNext = b->pNext;
    b->pPrev = a->pPrev;

    if (a->pNext != NULL) {
      a->pNext->pPrev = a;
    }
    if (b->pPrev != NULL) {
      b->pPrev->pNext = b;
    }

    b->pNext = a;
    a->pPrev = b;
  } else if (b->pNext == a) { // B is directly before A, similar handling
    b->pNext = a->pNext;
    a->pPrev = b->pPrev;

    if (b->pNext != NULL) {
      b->pNext->pPrev = b;
    }
    if (a->pPrev != NULL) {
      a->pPrev->pNext = a;
    }

    a->pNext = b;
    b->pPrev = a;
  } else { // Non-adjacent nodes
    Course *tempPrev = a->pPrev;
    Course *tempNext = a->pNext;

    a->pPrev = b->pPrev;
    a->pNext = b->pNext;

    b->pPrev = tempPrev;
    b->pNext = tempNext;

    if (a->pNext != NULL) {
      a->pNext->pPrev = a;
    }
    if (a->pPrev != NULL) {
      a->pPrev->pNext = a;
    }

    if (b->pNext != NULL) {
      b->pNext->pPrev = b;
    }
    if (b->pPrev != NULL) {
      b->pPrev->pNext = b;
    }
  }

  // Update the list's head and tail if necessary
  if (courseList->pHead == a) {
    courseList->pHead = b;
  } else if (courseList->pHead == b) {
    courseList->pHead = a;
  }

  if (courseList->pTail == a) {
    courseList->pTail = b;
  } else if (courseList->pTail == b) {
    courseList->pTail = a;
  }
}

void sort(List *courseList) {
  if (!courseList || courseList->size < 2) {
    return;
  }

  bool swapped;
  do {
    swapped = false;
    Course *current = courseList->pHead;
    while (current->pNext != NULL) {
      if (current->name[0] > current->pNext->name[0]) {
        swap(courseList, current, current->pNext);
        // Now current points to current->pPrev
        if (current->pPrev != NULL) {
          current = current->pPrev;
        }
        swapped = true;
      } else {
        current = current->pNext;
      }
    }
  } while (swapped);
}
