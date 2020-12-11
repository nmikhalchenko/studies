//Вариант 5

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "shared_code/shared_code.h"

#define INPUT_BUFFER_SIZE (128)

#define ERRORMSG(msg) (fprintf(stderr, msg), puts(""))

void requestInputToFile(FILE* file, int maxLines)
{
    if (!file)
    {
        ERRORMSG("NULL FILE POINTER!");
        return;
    }

    char buffer[INPUT_BUFFER_SIZE];
    for (int i = 0; i < maxLines; i++)
    {
        printf("Enter line number %i: ", i + 1);
        requestString(sizeof(buffer), buffer, NULL);

        char* lastChar = &buffer[strlen(buffer)];
        if (*lastChar != '\n' && i < maxLines - 1)
        {
            strncat(buffer, "\n", sizeof(buffer) - 1);
        }

        fprintf(file, "%s", buffer);
    }
}

void writeEvenLines(FILE* dest, FILE* src)
{
    if (!dest || !src)
    {
        fprintf(stderr, "NULL FILE POINTER!");
    }

    char buffer[INPUT_BUFFER_SIZE];
    int line = 0;
   
    while (fgets(buffer, sizeof(buffer), src))
    {
        line++;
        bool isEven = (line % 2) == 0;
        if (isEven)
        {
            fprintf(dest, "%s", buffer);
        }
    }
}

#define INPUT_FILENAME ("input.txt")
#define OUTPUT_FILENAME ("output.txt")

int main(void)
{
    FILE* input = fopen(INPUT_FILENAME, "w");
    if (!input)
    {
        ERRORMSG("FAILED TO OPEN INPUT FILE FOR WRITING");
    }

    requestInputToFile(input, 10);
    
    input = freopen(INPUT_FILENAME, "r", input);
    if (!input)
    {
        ERRORMSG("FAILED TO OPEN INPUT FILE FOR READING");
    }
    
    FILE* output = fopen(OUTPUT_FILENAME, "w");
    if (!output)
    {
        ERRORMSG("FAILED TO OPEN OUTPUT FILE FOR WRITING");
    }

    writeEvenLines(output, input);

    fclose(input);
    fclose(output);

    return 0;
}
