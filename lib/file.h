#ifndef FILE_H
#define FILE_H
#include "component.h"
void writeListToFile(const char *filename, List *list);
bool readListFromFile(const char *filename, List *courseList);
bool deleteData();
#endif // !FILE_H
