// Copyright 2024 <Pham Xuan Hoang>
// Guard the headers
#ifndef COMPONENT_H
#define COMPONENT_H
#include <stdbool.h>

typedef struct _Node {
  double attendance, assignment, midterm, final, bonus, average;
  int attendP, assignP, midtermP, finalP, bonusP, ects;
  struct _Node *pNext;
  struct _Node *pPrev;
  char name[];
} Course;

typedef struct _List {
  int size;
  double targetedGPA;
  double currentGPA;
  Course *pHead;
  Course *pTail;
} List;

void init(List *newList);
Course *initCourse(int bufferSize);
bool isEmpty(List *courseList);
void insert(Course *newCourse, List *courseList);
void removeCourse(List *courseList, char *name);
void editCourse(List *courseList, char *name);
void showAllCourse(List *courseList);
double calculateAverage(double attendance, int attendP, double assignment, int assignP, double midterm, int midtermP, double final, int finalP, double bonus, int bonusP);
double calculateGPA(List *courseList);
void predictGPA(List *courseList);
int calculateCurrentECTs(List *courseList);
void changeTargetedGPA(List *courseList);
#endif // !COMPONENT_H
