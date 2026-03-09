/*
** EPITECH PROJECT, 2026
** my_strcmp
** File description:
** my strcmp
*/

#include "my.h"

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] < s2[i])
            return (-1);
        if (s2[i] < s1[i])
            return (1);
        if (s1[i + 1] == '\0' && s2[i + 1] != '\0')
            return (-1);
        if (s1[i + 1] != '\0' && s2[i + 1] == '\0')
            return (1);
        i++;
    }
    return (0);
}
