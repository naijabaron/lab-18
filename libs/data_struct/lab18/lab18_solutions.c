#include "lab18_solutions.h"
#include "../string/string.h"

void removeExtraSpaces(char* source) {
    char* writePointer = source;
    while (*source != '\0') {
        if (*source != *(source + 1)) {
            *writePointer = *source;
            writePointer++;
        }
        source++;
    }
    *writePointer = '\0';
}
int getWord(char *beginSearch, WordDescriptor* word) {
    word->begin = findNonSpace(beginSearch);

    if (*word->begin == '\0') {
        return 0;
    }

    word->end = findSpace(word->begin);

    return 1;
}

int getWordReverse(char* searchEnd, char* searchStart, WordDescriptor* word) {
    word->end = findNonSpaceReverse(searchEnd, searchStart) + 1;

    if (word->end == searchEnd + 1) {
        word->begin = searchStart + 1;
        return 0;
    }

    word->begin = findSpaceReverse(searchEnd, word->end - 1) + 1;

    return 1;
}

void forEachWord(char* string, void (*function)(WordDescriptor)) {
    char* searchPoint = string;
    WordDescriptor word;

    while (getWord(searchPoint, &word)) {
        function(word);

        searchPoint = word.end;
    }
}

static bool isDigit(char character) {
    return isdigit(character);
}

static bool isAlpha(char character) {
    return isalpha(character);
}

void lettersToStartDigitsToEnd(WordDescriptor word) {
    char* stringBufferEnd = copy(word.begin, word.end, string_buffer);
    char* digitsEnd = copyIf(string_buffer, stringBufferEnd, word.begin, isAlpha);

    copyIf(string_buffer, stringBufferEnd, digitsEnd, isDigit);
}

void replaceDigitsBySpaces(char* string) {
    char* readPoint = string;
    char* writePoint = string_buffer;

    while (*readPoint != '\0') {
        if (isdigit(*readPoint)) {
            int digit = *readPoint - '0';

            for (int i = 0; i < digit; i++) {
                *writePoint = ' ';
                writePoint++;
            }
        } else {
            *writePoint = *readPoint;
            writePoint++;
        }
        readPoint++;
    }

    *copy(string_buffer, writePoint, string) = '\0';
}

int compareWords(WordDescriptor left, WordDescriptor right) {
    while (left.begin != left.end && right.begin != right.end && *left.begin == *right.begin) {
        left.begin++;
        right.begin++;
    }

    if (left.begin == left.end && right.begin == right.end) {
        return 0;
    }

    if (left.begin == left.end && right.begin != right.end) {
        return -(*right.begin);
    }

    if (left.begin != left.end && right.begin == right.end) {
        return *left.begin;
    }

    return *left.begin - *right.begin;
}
void replace(char* string, char* replaceable, char* replacement) {
    size_t replaceableLength = getLength(replaceable);
    size_t replacementLength = getLength(replacement);
    WordDescriptor replaceableWord = {replaceable, replaceable + replaceableLength};
    WordDescriptor replacementWord = {replacement, replacement + replacementLength};
    char* readPoint;
    char* writePoint;

    if (replaceableLength > replacementLength) {
        readPoint = string;
    } else {
        *copy(string, string + getLength(string), string_buffer) = '\0';
        readPoint = string_buffer;
    }

    writePoint = string;
    WordDescriptor cur_word;

    while (getWord(readPoint, &cur_word)) {
        writePoint = copy(readPoint, cur_word.begin, writePoint);

        if (compareWords(cur_word, replaceableWord) == 0) {
            writePoint = copy(replacementWord.begin, replacementWord.end, writePoint);
        } else {
            writePoint = copy(cur_word.begin, cur_word.end, writePoint);
        }

        readPoint = cur_word.end;
    }

    *writePoint = '\0';
}