/*
** EPITECH PROJECT, 2026
** my_strcpy.c
** File description:
** copy a string
*/

#include "my.h"

char *my_strcpy(char *dest, char const *src)
{
    uint64_t i = 0;

    for (; i < my_strlen(src); i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}
