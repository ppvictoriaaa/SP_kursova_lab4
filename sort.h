#ifndef SORT
#define SORT
#include "stringProcessor.h"
void swap(char** a, char** b)
{
    char* temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(char** arr, size_t length)
{
    if (length <= 1)
        return;

    char* pivot = arr[length - 1];
    size_t i = 0;

    for (size_t j = 0; j < length - 1; j++)
    {
        if (strcmp(arr[j], pivot) <= 0)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }

    swap(&arr[i], &arr[length - 1]);

    quick_sort(arr, i);
    quick_sort(arr + i + 1, length - i - 1);
}

#endif // !SORT