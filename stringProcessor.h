#ifndef STRING_PROCESSOR
#define STRING_PROCESSOR

#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>
#include <ctype.h>
#include <stdio.h>
#include "sort.h"

#define STRING_MAX 512

// Функція для зчитування рядка
const int32_t get_str(const char* msg, char* str, const int32_t limit)
{
    printf("%s", msg);
    int i = 0;
    char c;
    while (i < limit - 1 && (c = getchar()) != EOF && c != '\n')
    {
        str[i++] = c;
    }
    str[i] = '\0'; // нульовий символ
    return i;
}

// Функція для визначення довжини рядка
const size_t strlenn(const char* str)
{
    size_t len = 0;
    while (str[len] != '\0')
    {
        ++len;
    }
    return len;
}

// Функція для копіювання рядка
void strcopy(char* fStr, char* sStr, size_t until)
{
    size_t i = 0;
    while (i < until && sStr[i] != '\0')
    {
        fStr[i] = sStr[i];
        ++i;
    }
    fStr[i] = '\0'; // нульовий символ
}

// Функція для порівняння двох рядків
int32_t strcmpp(const char* fStr, const char* sStr)
{
    while (*fStr && (*fStr == *sStr))
    {
        ++fStr;
        ++sStr;
    }
    return (*(unsigned char*)fStr - *(unsigned char*)sStr);
}

// Функція для додавання одного рядка до кінця іншого
char* strcatt(char* fStr, const char* sStr)
{
    char* ptr = fStr + strlenn(fStr);
    while (*sStr != '\0')
    {
        *ptr++ = *sStr++;
    }
    *ptr = '\0'; //нульовий символ
    return fStr;
}

// Функція перевірки валідності рядка
bool is_string_valid(char* str)
{
    bool isThereString = false;
    bool isThereColon = false;
    const size_t size = strlenn(str);

    for (size_t i = 0; i < size; i++)
    {
        if ((str[i] == ':' || str[i] == ';' || str[i] == ',') && i == 0)
        {
            return false;
        }
        if (str[i] == ':')
        {
            isThereColon = true;
        }
        else if (isThereColon)
        {
            if (str[i] == ',')
            {
                if (!isalpha(str[i - 1]) && str[i - 1] != ' ')
                {
                    return false;
                }
                else
                {
                    isThereString = true;
                }
            }
            if (str[i] == ';')
            {
                if (!isThereString || (!isalpha(str[i - 1]) && str[i - 1] != ' '))
                {
                    return false;
                }
                else
                {
                    isThereColon = false;
                }
            }
            if (str[i] == ':')
            {
                return false;
            }
        }
        else
        {
            isThereString = false;
        }
    }
    return true;
}

// Функція для обробки рядка
char* process_string(char* str)
{
    const size_t length = strlenn(str);
    char* result = (char*)calloc(length + 1, sizeof(char)); 

    for (size_t i = 0; i < length; i++)
    {
        if (str[i] != ':')
        {
            char temp[2] = { str[i], '\0' };
            strcatt(result, temp);
            continue;
        }
        if (str[i + 1] != ' ')
        {
            return NULL;
        }
        strcatt(result, ": ");
        const size_t strsPreCnt = 100;
        char** arr = (char**)calloc(strsPreCnt, sizeof(char*));
        for (size_t strsCnt = 0; strsCnt < strsPreCnt; strsCnt++)
        {
            arr[strsCnt] = (char*)calloc(STRING_MAX, sizeof(char));
        }

        for (size_t j = i + 2, strRealCnt = 0; j < length; j++)
        {
            if (str[j] == ',')
            {
                ++strRealCnt;
                ++j;
            }
            else if (str[j] == ';')
            {
                quick_sort(arr, ++strRealCnt);
                for (size_t k = 0; k < strRealCnt; k++)
                {
                    strcatt(result, arr[k]);
                    if (k == strRealCnt - 1)
                    {
                        strcatt(result, ";");
                    }
                    else
                    {
                        strcatt(result, ", ");
                    }
                }
                i = j;
                break;
            }
            else
            {
                char temp[2] = { str[j], '\0' };
                strcatt(arr[strRealCnt], temp);
            }
        }

        for (size_t strsCnt = 0; strsCnt < strsPreCnt; strsCnt++)
        {
            free(arr[strsCnt]);
        }
        free(arr);
    }
    return result;
}

#endif
