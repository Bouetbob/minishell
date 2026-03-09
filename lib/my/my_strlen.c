/*
** EPITECH PROJECT, 2026
** str len
** File description:
** str len
*/

#include <stdint.h>

uint64_t my_strlen(char const *str)
{
    uint64_t count = 0;

    while (*str != '\0'){
        str++;
        count++;
    }
    return (count);
}
