#ifndef OP_LAB_17_LAB18_SOLUTIONS_H
#define OP_LAB_17_LAB18_SOLUTIONS_H

#define ASCII_SYMBOLS_AMOUNT 256

typedef struct WordDescriptor {
    char* begin;
    char* end;
} WordDescriptor;

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

static BagOfWords bag1;
static BagOfWords bag2;

typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;

#include "../string/string.h"

void removeExtraSpaces(char* source);

int getWord(char* beginSearch, WordDescriptor* word);

int getWordReverse(char* searchEnd, char* searchStart, WordDescriptor* word);

void forEachWord(char* string, void (*function)(WordDescriptor));

void lettersToStartDigitsToEnd(WordDescriptor word);

void replaceDigitsBySpaces(char* string);

int compareWords(WordDescriptor left, WordDescriptor right);

void replace(char* string, char* replaceable, char* replacement);

bool areWordsSorted(char* string);

void outputWordsInReverseOrder(char* string);

int countPalindromes(char* string);

void mixWords(char* left, char* right, char* destination);

void reverseWordsOrder(char* string);

void printWord(WordDescriptor word);

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithSymbol(char* string, WordDescriptor* word, char symbol);

bool findLastEqualWordInBothStr(char* string, char* word, WordDescriptor* lastWord);

bool hasStringEqualWords(char* string);

bool hasStrWordsFromEqualSymbols(char* string);

void getStrFromWordsNotEqualToTheLast(char* string);

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordInBothStr(char* string, char* word, WordDescriptor* wordDst);

#endif //OP_LAB_17_LAB18_SOLUTIONS_H