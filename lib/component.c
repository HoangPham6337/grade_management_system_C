// Copyright 2024 <Pham Xuan Hoang>
#include "input.h"
#include "component.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init(List *newList) {
  if (newList == NULL) {
    printf("Failed to initialized list, exiting...\n");
    return;
  }
  newList->size = 0;
  newList->targetedGPA = validate_double("Enter targeted GPA: ");
  newList->pHead = NULL;
  newList->pTail = NULL;
}

Course *initCourse(int bufferSize) {
  char *name = validate_string("Enter course name: ", bufferSize);

  double attendance = validate_double("Enter attendance score: ");
  int attendP = validate_int("Enter attendance percentage: ");
  
  double assignment = validate_double("Enter assignment score: ");
  int assignP = validate_int("Enter assignment percentage: ");

  double bonus = validate_double("Enter bonus score: ");
  int bonusP = validate_double("Enter bonus percentage: ");

  double midterm = validate_double("Enter midterm score: ");
  int midtermP = validate_int("Enter midterm percentage: ");

  double final = validate_double("Enter final score: ");
  int finalP = validate_int("Enter final percentage: ");

  int ects = validate_int("Enter ECTs: ");

  // Ensure the allocated memory can hold the string name
  size_t size = sizeof(Course) + strlen(name) + 1;
  Course *newCourse = (Course *)malloc(size);
  if (newCourse == NULL) {
    printf("Failed to allocate memory for Course. Exiting()");
    exit(1);
  }
  // Set value to newCourse
  newCourse->attendance = attendance;
  newCourse->attendP = attendP;

  newCourse->assignment = assignment;
  newCourse->assignP = assignP;

  newCourse->midterm = midterm;
  newCourse->midtermP = midtermP;

  newCourse->final = final;
  newCourse->finalP = finalP;

  newCourse->bonus = bonus;
  newCourse->bonusP = bonusP;

  newCourse->average = calculateAverage(attendance, attendP, assignment, assignP, midterm, midtermP, final, finalP, bonus, bonusP);

  newCourse->ects = ects;
  strcpy(newCourse->name, name);
  newCourse->pNext = NULL;
  newCourse->pPrev = NULL;
  return newCourse;
}

bool isEmpty(List *courseList) { return (courseList->size == 0); }

void insert(Course *newCourse, List *courseList) {
  if (courseList == NULL) {
    printf("Failed to add course, NULL pointer encountered.\n");
    return;
  }
  if (isEmpty(courseList)) { // Add the first node
    courseList->size++;
    courseList->pHead = newCourse;
    courseList->pTail = newCourse;
    return;
  }
  Course *current = courseList->pHead;
  for (int i = 0; i < courseList->size - 1;
       ++i) {                 // Move the pointer to the end
    current = current->pNext; // This will not go out of bound
  }
  current->pNext = newCourse;
  newCourse->pPrev = current;
  courseList->size++;
  courseList->pTail = newCourse;
}

void removeCourse(List *courseList, char *name) {
  if (courseList->size == 0) {
    printf("Course list empty, nothing to delete.\n");
    return;
  }
  Course *current = courseList->pHead;
  Course *previous = NULL;

  if (courseList->size == 1) { // Handle case where there is 1 node
    if (strcmp(current->name, name) == 0) {
      free(current);
      courseList->pHead = NULL;
      courseList->pTail = NULL;
      courseList->size--;
      printf("Course found, course deleted.\n");
    }
    return;
  }
  while (current != NULL) { // General case
    if (strcmp(current->name, name) == 0) {
      if (current->pNext == NULL) { // Last node
        courseList->pTail = current->pPrev;
        current->pPrev->pNext = NULL;
      } else if (previous == NULL) { // First node
        courseList->pHead = current->pNext;
        current->pNext->pPrev = NULL;
      } else { // Any node
        previous->pNext = current->pNext;
        current->pNext->pPrev = current->pPrev;
      }
      courseList->size--;
      free(current);
      printf("Course found, course deleted.\n");
      return;
    }
    previous = current;
    current = current->pNext;
  }
  printf("Course not found, please try again!\n");
}

void editCourse(List *courseList, char *name) {
  if (courseList->size == 0) {
    printf("Course list empty, nothing to edit.\n");
    return;
  }
  Course *current = courseList->pHead;
  if (courseList->size == 1) { // Handle case where there is 1 node
    if (strcmp(current->name, name) != 0) {
      printf("Course not found!\n");
      return;
    }
  }
  while (current != NULL) { // General case
    if (strcmp(current->name, name) == 0) {
      break;
    }
    current = current->pNext;
  }
  if (current == NULL) {
    printf("Course not found, please try again!\n");
    return;
  }
  printf("%-30s | %4s | %10s | %8s | %10s | %8s | %7s | %9s | %5s | %7s | %5s | %7s | %7s |\n", 
      "Course Name", "ECTs", "Attendance", "Attend %", "Assignment", "Assign %", "Midterm", "Midterm %", "Final", "Final %", "Bonus", "Bonus %", "Average");
  printf("-------------------------------+------+------------+----------+------------+----------+---------+-----------+-------+---------+-------+---------+---------+\n");
    printf("%-30s | %4d | %10.2lf | %7d%% | %10.2lf | %7d%% | %7.2lf | %8d%% | %5.2lf | %6d%% | %5.2lf | %6d%% | %7.2lf |\n",
        current->name,
        current->ects,
        current->attendance,
        current->attendP,
        current->assignment,
        current->assignP,
        current->midterm,
        current->midtermP,
        current->final,
        current->finalP,
        current->bonus,
        current->bonusP,
        current->average);
  printf("-------------------------------+------+------------+----------+------------+----------+---------+-----------+-------+---------+-------+---------+---------+\n");

  double attendance = validate_double("Enter attendance score: ");
  int attendP = validate_int("Enter attendance percentage: ");
  
  double assignment = validate_double("Enter assignment score: ");
  int assignP = validate_int("Enter assignment percentage: ");

  double bonus = validate_double("Enter bonus score: ");
  int bonusP = validate_double("Enter bonus percentage: ");

  double midterm = validate_double("Enter midterm score: ");
  int midtermP = validate_int("Enter midterm percentage: ");

  double final = validate_double("Enter final score: ");
  int finalP = validate_int("Enter final percentage: ");

  int ects = validate_int("Enter ECTs: ");

  current->attendance = attendance;
  current->attendP = attendP;

  current->assignment = assignment;
  current->assignP = assignP;

  current->midterm = midterm;
  current->midtermP = midtermP;

  current->final = final;
  current->finalP = finalP;

  current->bonus = bonus;
  current->bonusP = bonusP;

  current->average = calculateAverage(attendance, attendP, assignment, assignP, midterm, midtermP, final, finalP, bonus, bonusP);

  current->ects = ects;
}

void showAllCourse(List *courseList) {
  if (courseList->size == 0) {
        printf("List empty, nothing to show!\n");
        return;
    }
    Course *current = courseList->pHead;

    printf("No %-30s | %4s | %10s | %8s | %10s | %8s | %7s | %9s | %5s | %7s | %5s | %7s | %7s |\n", 
        "Course Name", "ECTs", "Attendance", "Attend %", "Assignment", "Assign %", "Midterm", "Midterm %", "Final", "Final %", "Bonus", "Bonus %", "Average");
    printf("----------------------------------+------+------------+----------+------------+----------+---------+-----------+-------+---------+-------+---------+---------+\n");
    // Iterate through the course list
    int count = 0;
    while (current != NULL) {
        printf("%2d %-30s | %4d | %10.2lf | %7d%% | %10.2lf | %7d%% | %7.2lf | %8d%% | %5.2lf | %6d%% | %5.2lf | %6d%% | %7.2lf |\n",
            count++,
            current->name,
            current->ects,
            current->attendance,
            current->attendP,
            current->assignment,
            current->assignP,
            current->midterm,
            current->midtermP,
            current->final,
            current->finalP,
            current->bonus,
            current->bonusP,
            current->average);

        current = current->pNext;
    }
    printf("----------------------------------+------+------------+----------+------------+----------+---------+-----------+-------+---------+-------+---------+---------+\n");
  printf("GPA: %.3lf\n", calculateGPA(courseList));
}

double calculateAverage(double attendance, int attendP, double assignment, int assignP, double midterm, int midtermP, double final, int finalP, double bonus, int bonusP) {
    double attendanceWeight = attendance * attendP / 100.0;
    double assignmentWeight = assignment * assignP / 100.0;
    double midtermWeight = midterm * midtermP / 100.0;
    double finalWeight = final * finalP / 100.0;
    double bonusWeight = bonus * bonusP / 100.0;

    return attendanceWeight + assignmentWeight + midtermWeight + finalWeight + bonusWeight;
}

double calculateGPA(List *courseList) {
  Course *current = courseList->pHead;
  int totalECTs = 0;
  double totalAverage = 0;
  for (int i = 0; i < courseList->size; ++i) {
    totalECTs += current->ects;
    totalAverage += current->average * current->ects;
    current = current->pNext;
    if (!current) {
      break;
    }
  }
  return totalAverage / totalECTs;
}

int calculateCurrentECTs(List *courseList) {
  Course *current = courseList->pHead;
  int currentECTs = 0;
  while (current) {
    currentECTs += current->ects;
    current = current->pNext;
  }
  return currentECTs;
}

void predictGPA(List *courseList) {
  printf("Current GPA: %.2lf\n", calculateGPA(courseList));
  Course *current = courseList->pHead;
  // int ects = validate_int("Enter the ECTs of predicted course: ");
  // int totalECTs = ects;
  // double totalAverage = 0;
  // for (int i = 0; i < courseList->size; ++i) {
  //   totalECTs += current->ects;
  //   totalAverage += current->average * current->ects;
  //   current = current->pNext;
  //   if (!current) {
  //     break;
  //   }
  // }
  // double neededAvg = (courseList->targetedGPA * totalECTs - totalAverage) / ects;
  // if (neededAvg > 20) {
  //   neededAvg = (courseList->targetedGPA * (totalECTs + ects) - totalAverage) / (ects * 2);
  //   if (neededAvg > 20) {
  //     neededAvg = (courseList->targetedGPA * (totalECTs + ects) - totalAverage) / (ects * 3);
  //     printf("Need to achieve an average of %.3lf in the next 3 %dECTs course to meet the targeted GPA of: %.3lf", neededAvg, ects, courseList->targetedGPA);
  //   } else {
  //     printf("Need to achieve an average of %.3lf in the next 2 %dECTs course to meet the targeted GPA of: %.3lf", neededAvg, ects, courseList->targetedGPA);
  //   }
  // } else {
  //   printf("Need to achieve an average of %.3lf in the next course to meet the targeted GPA of: %.3lf", neededAvg, courseList->targetedGPA);
  // }


  int totalECTs = 60;
  int currentECTs = calculateCurrentECTs(courseList);
  double totalAverage = 0;
  while (current) {
    totalAverage += current->average * current->ects;
    current = current->pNext;
  }
  printf("Current ECTS: %d\n", currentECTs);

  double neededAvgAllCourses = (courseList->targetedGPA * totalECTs - totalAverage) / (totalECTs - currentECTs);
  printf("You need on average of %.3lf for %d remaining ECTs to achieve %.2lf targeted GPA", neededAvgAllCourses, totalECTs - currentECTs, courseList->targetedGPA);
}

void changeTargetedGPA(List *courseList) {
  double newGPA = validate_double("Enter new targeted GPA: ");
  courseList->targetedGPA = newGPA;
}
