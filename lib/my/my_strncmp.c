/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** my_strncmp
*/

#include "my.h"
#include <stddef.h>
#include <stdint.h>

int my_strncmp(const char *s1, const char *s2, uint64_t n)
{
    uint64_t i = 0;

    while (s1[i] != '\0' && s2[i] != '\0' && i < n) {
        if (s1[i] < s2[i])
            return (-1);
        if (s2[i] < s1[i])
            return (1);
        i++;
    }
    return (0);
}
