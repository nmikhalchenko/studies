//Вариант 5

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "shared_code/shared_code.h"

bool isFitForWords(char c, bool checkIfAlpha)
{
    return  (isalpha(c) || !checkIfAlpha) &&
            (c != '\0') &&
            (c != ' ');
}

int getWords(const char* str, char delim, bool onlyAlpha, int outsize, int starts[outsize], int ends[outsize])
{
    int currentPair = 0;

    int len = strlen(str) + 1;
    for (int i = 0; i < len; i++)
    {
        char c = str[i];
        bool hasPrev = i - 1 >= 0;
        char prev = str[i - 1];

        if (isFitForWords(c, onlyAlpha))
        {
            if ((hasPrev && !isFitForWords(prev, onlyAlpha)) || !hasPrev)
            {
                starts[currentPair] = i;
            }
        }
        else
        {
            if (hasPrev && isFitForWords(prev, onlyAlpha))
            {
                ends[currentPair] = i;
                currentPair++;

                if (currentPair >= outsize)
                {
                    break;
                }
            }
        }
    }

    return currentPair;
}

// Debug tool
/*
void displayWord(const char* base, int start, int end)
{
    for (int i = start; i < strlen(base) && i < end; i++)
    {
        printf("%c", base[i]);
    }
    puts("");
}
*/

void longestWord(const char* str, char delim, int outsize, char output[outsize])
{
    int len = strlen(str);
    int* starts = (int*)calloc(len, sizeof(int));
    int* ends = (int*)calloc(len, sizeof(int));
    int wordCount = getWords(str, delim, true, len, starts, ends);

    int maxLength = 0;
    int maxIndex = 0;
    for (int i = 0; i < wordCount; i++)
    {
        int wordLength = ends[i] - starts[i];
        if (wordLength > maxLength)
        {
            maxLength = wordLength;
            maxIndex = i;
        }
    }

    int actualSize = outsize > maxLength ? maxLength + 1 : outsize;
    for (int i = 0; i < actualSize; i++)
    {
        int index = starts[maxIndex] + i;
        output[i] = i == maxLength ? '\0' : str[index];
    }

    free(starts);
    free(ends);
}

int main(void)
{
    char buffer[256] = {0};
    printf("%li\n", strlen(buffer));
    requestString(sizeof(buffer), buffer, "Enter a few words: ");
    printf("%li\n", strlen(buffer));

    char longest[64];
    longestWord(buffer, ' ', sizeof(longest), longest);

    printf("The longest word is \"%s\"\n", longest);

    return 0;
}