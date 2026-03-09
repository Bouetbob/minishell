/*
** EPITECH PROJECT, 2026
** my_strdup.c
** File description:
** malloc a strings
*/

#include "my.h"
#include <stdlib.h>

char *my_strdup(char const *src)
{
    char *dest = malloc(sizeof(char) * (my_strlen(src)) + 1);

    dest = my_strcpy(dest, src);
    return dest;
}
