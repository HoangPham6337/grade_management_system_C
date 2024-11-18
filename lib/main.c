// Copyright 2024 <Pham Xuan Hoang>
#include "component.h"
#include "file.h"
#include "input.h"
#include "sorting.h"
#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>

void UILoop(List *courseList);

bool dataDeleted = false;
int main() {
  printf("GPA management program\n");
  printf("Constructing course list...\n");
  List *courseList = (List *)malloc(sizeof(List));
  if (courseList == NULL) {
    printf("Fatal error, failed to allocate memory, exiting...\n");
    return 1;
  }
  if (!readListFromFile("data.dat", courseList)) {
    init(courseList);
    courseList->targetedGPA = 18;
  }
  UILoop(courseList);
  if (!dataDeleted) {
    writeListToFile("data.dat", courseList);
  }
  // Take care variable init by malloc()
  freeList(courseList);
  return 0;
}

void UILoop(List *courseList) {
  int choice;
  int bufferSize = 30;
  char message[] = {"1. Enter new course and mark.\n2. Display all data.\n3. "
                    "Remove a course.\n4. Edit a course\n5. Predict require "
                    "GPA.\n6. Change targeted GPA\n7. Delete data.\n8. Exit.\n"};
  while (true) {
    clearScreen();
    printf("Targeted GPA: %.3lf\nCurrent GPA: %.3lf\nCurrent ECTs: %.d\n\n", courseList->targetedGPA, calculateGPA(courseList), calculateCurrentECTs(courseList));
    printf("%s", message);
    choice = validate_int("Enter your choice: ");
    switch (choice) {
    case (1): { // Add brackets to ensure scope stay within case 1
      clearScreen();
      insert(initCourse(bufferSize), courseList);
      sort(courseList);
      break;
    }
    case (2):
      clearScreen();
      showAllCourse(courseList);
      printf("Enter to continue.");
      getchar();
      break;
    case (3): {
      clearScreen();
      Course *current = courseList->pHead;
      int counter = 0;
      while (current != NULL) {
          printf("%d. %s\n", counter++, current->name);
          current = current->pNext;
        }

      char *name = validate_string("\nEnter course name to delete: ", bufferSize);

      printf("Are you sure? (Y/N) ");
      char choice = getchar();
      choice -= (choice > 97) ? (32) : (0);
      if (choice != 'Y')
          break;
      removeCourse(courseList, name);
      getchar();
      getchar();
      break;
    }
    case (4): {
      clearScreen();
      showAllCourse(courseList);
      printf("\n");
      char *name = validate_string("Enter course name: ", bufferSize);
      editCourse(courseList, name);
      getchar();
      break;
    }
    case (5):
      clearScreen();
      predictGPA(courseList);
      getchar();
      break;
    case (6):
      clearScreen();
      changeTargetedGPA(courseList);
      break;
    case (7):
      clearScreen();
      dataDeleted = deleteData();
      getchar();
      getchar();
      break;
    case (8):
      printf("Exiting...\n");
      return;
    }
    
  }
}
