/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** my_strcat
*/

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    int length = my_strlen(dest);

    for (uint64_t i = 0; i < my_strlen(src); i++)
        dest[length + i] = src[i];
    dest[length + my_strlen(src)] = '\0';
    return (dest);
}
