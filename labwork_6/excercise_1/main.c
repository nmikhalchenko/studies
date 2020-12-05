//Вариант 5

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "shared_code/shared_code.h"

int indexOfMaxAbsoluteInRange(int beg, int end, int length, float numbers[length])
{
    int index = beg;
    float max = abs(numbers[index]);

    for (int i = beg; (i <= end) && (i < length); i++)
    {
        float current = abs(numbers[i]);
        if (current > max)
        {
            index = i;
            max = current;
        }
    }

    return index;
}

int indexOfFirstPositiveInRange(int beg, int end, int length, float numbers[length])
{
    for (int i = beg; (i <= end) && (i < length); i++)
    {
        if (numbers[i] > 0)
            return i;
    }

    return -1;
}

float sumInExclusiveRange(int beg, int end, int length, float numbers[length])
{
    float sum = 0.0f;
    beg = beg < 0 ? 0 : beg;

    for (int i = beg + 1; (i < end) && (i < length); i++)
        sum += numbers[i];

    return sum;
}

int main(void)
{

    int size = requestSize("Enter array size: ");
    puts("");

    float* floats = (float*)calloc(size, sizeof(float));
    requestFloatArray(size, floats, "Enter array:\n", true);

    printf("Array: ");
    printFloatArray(size, floats, true);

    int maxAbsolute = indexOfMaxAbsoluteInRange(0, size, size, floats);
    int firstPositive = indexOfFirstPositiveInRange(0, size, size, floats);
    int secondPositive = indexOfFirstPositiveInRange(firstPositive + 1, size, size, floats);
    float sumBetweenPositives = sumInExclusiveRange(firstPositive, secondPositive, size, floats);

    printf("The following element's absolute value is the highest: %4.2f\n", floats[maxAbsolute]);
    printf("Sum of elements between the first two positive values: %4.2f\n", sumBetweenPositives);

    free(floats);

    return 0;
}
