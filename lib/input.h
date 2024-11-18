#ifndef INPUT_H
#define INPUT_H

int validate_int(const char *message);
double validate_double(const char *message);
char *validate_string(const char *message, int bufferSize);
void title_case(char *str);
#endif /* ifndef INPUT_H */
