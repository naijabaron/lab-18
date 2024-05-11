#ifndef LAB_17_OWN_STRING_H
#define LAB_17_OWN_STRING_H

#define CHAR_SIZE sizeof(char)

#include <memory.h>
#include <stdbool.h>

size_t getLength(const char* string);

char* find(char* start, const char* end, int character);

char* findNonSpace(char* string);

char* findSpace(char* string);

char* findNonSpaceReverse(const char* searchEnd, char* searchStart);

char* findSpaceReverse(const char* searchEnd, char* searchStart);

int compareStrings(char* left, char* right);

char* copy(const char* start, const char* end, char* destination);

char* copyIf(char* start, const char* end, char* destination, bool (*filter)(char));

char* copyIfReverse(char* reversedStart, const char* reversedEnd, char* destination, bool (*filter)(char));

#endif //LAB_17_OWN_STRING_H