#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void writeListToFile(const char *filename, List *courseList) {
  FILE *file = fopen(filename, "wb");
  if (!file) {
    perror("Failed to open file");
    return;
  }

  // Write targetedGPA and size of the list first
  fwrite(&courseList->targetedGPA, sizeof(double), 1, file);
  fwrite(&courseList->size, sizeof(int), 1, file);

  Course *current = courseList->pHead;
  while (current != NULL) {
    // Write numeric data directly
    fwrite(&current->attendance, sizeof(current->attendance), 1, file);
    fwrite(&current->assignment, sizeof(current->assignment), 1, file);
    fwrite(&current->midterm, sizeof(current->midterm), 1, file);
    fwrite(&current->final, sizeof(current->final), 1, file);
    fwrite(&current->bonus, sizeof(current->bonus), 1, file);
    fwrite(&current->average, sizeof(current->average), 1, file);

    // Write percentage and ECTS as integer values
    fwrite(&current->attendP, sizeof(current->attendP), 1, file);
    fwrite(&current->assignP, sizeof(current->assignP), 1, file);
    fwrite(&current->midtermP, sizeof(current->midtermP), 1, file);
    fwrite(&current->finalP, sizeof(current->finalP), 1, file);
    fwrite(&current->bonusP, sizeof(current->bonusP), 1, file);
    fwrite(&current->ects, sizeof(current->ects), 1, file);
    // Write name length + name
    size_t nameLen = strlen(current->name) + 1; // Include null terminator
    fwrite(&nameLen, sizeof(nameLen), 1, file);
    fwrite(current->name, sizeof(char), nameLen, file);

    current = current->pNext;
  }

  fclose(file);
}

bool readListFromFile(const char *filename, List *courseList) {
  FILE *file = fopen(filename, "rb");
  if (!file) {
    free(file);
    return false;
  }

  // Read targetedGPA and list size first
  fread(&courseList->targetedGPA, sizeof(double), 1, file);
  fread(&courseList->size, sizeof(int), 1, file);

  courseList->pHead = courseList->pTail = NULL;
  Course *previous = NULL;

  for (int i = 0; i < courseList->size; ++i) {
    double attendance, assignment, midterm, final, bonus, average;
    int attendP, assignP, midtermP, finalP, bonusP, ects;

    fread(&attendance, sizeof(double), 1, file);
    fread(&assignment, sizeof(double), 1, file);
    fread(&midterm, sizeof(double), 1, file);
    fread(&final, sizeof(double), 1, file);
    fread(&bonus, sizeof(double), 1, file);
    fread(&average, sizeof(double), 1, file);

    fread(&attendP, sizeof(int), 1, file);
    fread(&assignP, sizeof(int), 1, file);
    fread(&midtermP, sizeof(int), 1, file);
    fread(&finalP, sizeof(int), 1, file);
    fread(&bonusP, sizeof(int), 1, file);
    fread(&ects, sizeof(int), 1, file);

    // Read name length + name
    size_t nameLen;
    fread(&nameLen, sizeof(nameLen), 1, file);
    size_t size = sizeof(Course) + nameLen;
    // Allocate memory for the Course
    Course *current = (Course *)malloc(size);
    current->attendance = attendance;
    current->assignment = assignment;
    current->midterm = midterm;
    current->final = final;
    current->bonus = bonus;
    current->average = average;

    current->attendP = attendP;
    current->assignP = assignP;
    current->midtermP = midtermP;
    current->finalP = finalP;
    current->bonusP = bonusP;
    current->ects = ects;

    fread(current->name, sizeof(char), nameLen, file);

    current->pNext = NULL;
    current->pPrev = previous;

    // Link the new node into the list
    if (previous != NULL) {
      previous->pNext = current;
    } else {
      courseList->pHead = current; // First node
    }
    previous = current;
  }

  courseList->pTail = previous; // Last node

  fclose(file);
  return true;
}

bool deleteData() {
  printf("Are you sure? (Y/N) ");
  char choice = getchar();
  choice -= (choice > 97) ? (32) : (0);
  if (choice != 'Y')
    return false;
  if (remove("data.dat") == 0) {
    printf("Clear data successfully.\n");
  }
  return true;
}
