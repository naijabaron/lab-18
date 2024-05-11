#ifndef OP_LAB_17_LAB18_SOLUTIONS_H
#define OP_LAB_17_LAB18_SOLUTIONS_H

#include "../string/string.h"

void removeExtraSpaces(char* source);

int getWord(char* beginSearch, WordDescriptor* word);

int getWordReverse(char* searchEnd, char* searchStart, WordDescriptor* word);

void forEachWord(char* string, void (*function)(WordDescriptor));

void lettersToStartDigitsToEnd(WordDescriptor word);

#endif //OP_LAB_17_LAB18_SOLUTIONS_H