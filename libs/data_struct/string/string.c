#include "string.h"
#include <ctype.h>
#include <stdio.h>
#include <malloc.h>

size_t getLength(const char* string) {
    const char* end = string;

    while (*end != '\0') {
        end++;
    }

    return end - string;
}

char* find(char* start, const char* end, int character) {
    while (start != end && *start != character) {
        start++;
    }

    return start;
}

char* findNonSpace(char* string) {
    while (isspace(*string) && *string != '\0') {
        string++;
    }

    return string;
}

char* findSpace(char* string) {
    while (!isspace(*string) && *string != '\0') {
        string++;
    }

    return string;
}

char* findNonSpaceReverse(const char* searchEnd, char* searchStart) {
    while (--searchStart != searchEnd && isspace(*searchStart)) {
        searchStart--;
    }

    return searchStart;
}

char* findSpaceReverse(const char* searchEnd, char* searchStart) {
    while (searchStart != searchEnd && !isspace(*searchStart)) {
        searchStart--;
    }

    return searchStart;
}

int compareStrings(char* left, char* right) {
    char leftChar, rightChar;

    while ((leftChar = *(left++)) == (rightChar = *(right++)) && leftChar != '\0' && rightChar != '\0');

    if (leftChar > rightChar) return 1;

    return (leftChar == rightChar) ? 0 : -1;
}

char* copy(const char* start, const char* end, char* destination) {
    size_t length = end - start;

    memcpy(destination, start, CHAR_SIZE * length);

    return destination + length;
}

char* copyIf(char* start, const char* end, char* destination, bool (*filter)(char)) {
    while(start != end) {
        if (filter(*start)) {
            memcpy(destination++, start, CHAR_SIZE);
        }

        start++;
    }

    return destination;
}

char* copyIfReverse(char* reversedStart, const char* reversedEnd, char* destination, bool (*filter)(char)) {
    while(reversedStart != reversedEnd) {
        if (filter(*reversedStart)) {
            memcpy(destination++, reversedStart, CHAR_SIZE);
        }

        reversedStart--;
    }

    return destination;
}