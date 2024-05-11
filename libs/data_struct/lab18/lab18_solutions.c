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
bool areWordsSorted(char* string) {
    WordDescriptor previousWord;

    if (getWord(string, &previousWord)) {
        WordDescriptor currentWord;

        while (getWord(previousWord.end, &currentWord)) {
            if (compareWords(previousWord, currentWord) > 0) {
                return false;
            }

            previousWord = currentWord;
        }
    }

    return true;
}
static void getBagOfWords(char* searchStart, BagOfWords* bag) {
    size_t wordIndex = 0;

    while (getWord(searchStart, bag->words + wordIndex)) {
        searchStart = bag->words[wordIndex].end;
        wordIndex++;
    }

    bag->size = wordIndex;
}

void printWord(WordDescriptor word) {
    if (*word.begin == '\0') {
        return;
    }

    while (word.begin != word.end) {
        putc(*word.begin, stdout);
        word.begin++;
    }
}

void outputWordsInReverseOrder(char* string) {
    getBagOfWords(string, &bag1);

    for (size_t i = bag1.size - 1; i != -1; i--) {
        printWord(bag1.words[i]);
        putchar('\n');
    }
}

static bool isPalindrome(WordDescriptor word) {
    word.end--;

    while (word.begin < word.end) {
        if (*word.begin != *word.end) {
            return false;
        }

        word.begin++;
        word.end--;
    }

    return true;
}

int countPalindromes(char* string) {
    int count = 0;
    char* searchPoint = string;
    WordDescriptor word;

    while (getWord(searchPoint, &word)) {
        if (isPalindrome(word)) {
            count++;
        }

        searchPoint = word.end;
    }

    return count;
}

void mixWords(char* left, char* right, char* destination) {
    WordDescriptor word1, word2;
    bool isWord1Found, isWord2Found;
    char* searchStart1 = left;
    char* searchStart2 = right;
    char* dst = destination;

    while ((isWord1Found = getWord(searchStart1, &word1)),
            (isWord2Found = getWord(searchStart2, &word2)),
            isWord1Found || isWord2Found) {

        if (isWord1Found) {
            dst = copy(word1.begin, word1.end, dst);
            *dst++ = ' ';
            searchStart1 = word1.end;
        }

        if (isWord2Found) {
            dst = copy(word2.begin, word2.end, dst);
            *dst++ = ' ';
            searchStart2 = word2.end;
        }
    }

    *(dst - (dst != destination)) = '\0';
}

void reverseWordsOrder(char* string) {
    char* r_begin_src = string + getLength(string) - 1;
    char* r_end_src = string - 1;
    char* begin_dst = string_buffer;
    WordDescriptor word;
    while (getWordReverse(r_end_src, r_begin_src, &word)) {
        begin_dst = copy(word.begin, word.end, begin_dst);
        *begin_dst++ = ' ';
        r_begin_src = word.begin - 1;
    }
    *copy(string_buffer, begin_dst - (begin_dst != string_buffer), string) = '\0';
}

static bool isSymbolInWord(WordDescriptor word, const char symbol) {
    return find(word.begin, word.end, symbol) != word.end;
}

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithSymbol(char* string, WordDescriptor* word, char symbol) {
    WordDescriptor previousWord;

    if (getWord(string, &previousWord)) {
        if (!isSymbolInWord(previousWord, symbol)) {
            string = previousWord.end;
            WordDescriptor next_word;

            while (getWord(string, &next_word)) {
                if (isSymbolInWord(next_word, symbol)) {
                    *word = previousWord;
                    return WORD_FOUND;
                }

                previousWord = next_word;
                string = previousWord.end;
            }

            return NOT_FOUND_A_WORD_WITH_A;
        }

        return FIRST_WORD_WITH_A;
    }

    return EMPTY_STRING;
}

static bool isWordFound(char* string, WordDescriptor word) {
    WordDescriptor currentWord;

    while (getWord(string, &currentWord)) {
        if (compareWords(word, currentWord) == 0) {
            return true;
        }

        string = currentWord.end;
    }

    return false;
}

bool findLastEqualWordInBothStr(char* string, char* word, WordDescriptor* lastWord) {
    char* searchEnd = string - 1;
    char* searchStart = string + getLength(string) - 1;
    WordDescriptor currentWord;

    while (getWordReverse(searchEnd, searchStart, &currentWord)) {
        if (isWordFound(word, currentWord)) {
            *lastWord = currentWord;

            return true;
        }

        searchStart = currentWord.begin - 1;
    }

    return false;
}

static int wordComparator(const void* left, const void* right) {
    return compareWords(*(WordDescriptor *) left, *(WordDescriptor *) right);
}

bool hasStringEqualWords(char* string) {
    getBagOfWords(string, &bag1);

    qsort(bag1.words, bag1.size, sizeof(*bag1.words), wordComparator);

    for (size_t i = 1; i < bag1.size; i++) {
        if (compareWords(bag1.words[i], bag1.words[i - 1]) == 0) {
            return true;
        }
    }

    return false;
}
static int charComparator(const void* left, const void* right) {
    return *(char*) left - *(char*) right;
}

static void removeAdjacentEqualLettersInWord(WordDescriptor* word) {
    char* destinationStart = word->begin;
    char* sourceStart = word->begin;

    while (sourceStart != word->end) {
        if (*sourceStart != *(sourceStart + 1)) {
            *destinationStart = *sourceStart;
            destinationStart++;
        }

        sourceStart++;
    }

    word->end = destinationStart;
}

bool hasStrWordsFromEqualSymbols(char* string) {
    *copy(string, string + getLength(string), string_buffer) = '\0';
    getBagOfWords(string_buffer, &bag1);

    for (size_t i = 0; i < bag1.size; i++) {
        qsort(bag1.words[i].begin, bag1.words[i].end - bag1.words[i].begin, sizeof(char), charComparator);
        removeAdjacentEqualLettersInWord(&bag1.words[i]);
    }

    qsort(bag1.words, bag1.size, sizeof(*bag1.words), wordComparator);

    for (size_t i = 1; i < bag1.size; i++) {
        if (compareWords(bag1.words[i], bag1.words[i - 1]) == 0) {
            return true;
        }
    }

    return false;
}

void getStrFromWordsNotEqualToTheLast(char* string) {
    char* end = string - 1;
    char* start = string + getLength(string) - 1;
    WordDescriptor lastWord;
    getWordReverse(end, start, &lastWord);
    char* sourceStart = string;
    char* destinationStart = string;
    WordDescriptor currentWord;

    while (getWord(sourceStart, &currentWord)) {
        if (compareWords(currentWord, lastWord) != 0) {
            destinationStart = copy(currentWord.begin, currentWord.end, destinationStart);
            *destinationStart++ = ' ';
        }

        sourceStart = currentWord.end;
    }

    *(destinationStart - (destinationStart != string)) = '\0';
}

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordInBothStr(char* string, char* word, WordDescriptor* wordDst) {
    WordDescriptor previousWord;

    if (getWord(string, &previousWord)) {
        if (!isWordFound(word, previousWord)) {
            string = previousWord.end;
            WordDescriptor nextWord;

            while (getWord(string, &nextWord)) {
                if (isWordFound(word, nextWord)) {
                    *wordDst = previousWord;
                    return WORD_FOUND;
                }

                previousWord = nextWord;
                string = previousWord.end;
            }

            return NOT_FOUND_A_WORD_WITH_A;
        }

        return FIRST_WORD_WITH_A;
    }

    return EMPTY_STRING;
}

void removePalindromes(char* string) {
    char* sourceStart = string;
    char* destinationStart = string;
    WordDescriptor currentWord;

    while (getWord(sourceStart, &currentWord)) {
        destinationStart = copy(sourceStart, currentWord.begin, destinationStart);

        if (!isPalindrome(currentWord)) {
            destinationStart = copy(currentWord.begin, currentWord.end, destinationStart);
        }

        sourceStart = currentWord.end;
    }

    *copy(sourceStart, string + getLength(string), destinationStart) = '\0';
}

void removePalindromes(char* string) {
    char* sourceStart = string;
    char* destinationStart = string;
    WordDescriptor currentWord;

    while (getWord(sourceStart, &currentWord)) {
        destinationStart = copy(sourceStart, currentWord.begin, destinationStart);

        if (!isPalindrome(currentWord)) {
            destinationStart = copy(currentWord.begin, currentWord.end, destinationStart);
        }

        sourceStart = currentWord.end;
    }

    *copy(sourceStart, string + getLength(string), destinationStart) = '\0';
}

void addWordsToShorterStr(char* left, char* right) {
    getBagOfWords(left, &bag1);
    getBagOfWords(right, &bag2);
    char *leftStart = findNonSpaceReverse(left - 1, left + getLength(left) - 1) + 1;

    for (size_t i = bag1.size; i < bag2.size; i++) {
        *leftStart++ = ' ';
        leftStart = copy(bag2.words[i].begin, bag2.words[i].end, leftStart);
    }

    char *rightStart = findNonSpaceReverse(right - 1, right + getLength(right) - 1) + 1;

    for (size_t i = bag2.size; i < bag1.size; i++) {
        *rightStart++ = ' ';
        rightStart = copy(bag1.words[i].begin, bag1.words[i].end, rightStart);
    }

    *leftStart = '\0';
    *rightStart = '\0';
}

