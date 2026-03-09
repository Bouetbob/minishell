/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** my_get_array_size
*/

#include <stdint.h>
#include <stdio.h>

int my_get_array_size(char **array)
{
    int size = 0;

    while (array[size] != NULL)
        size++;
    return size;
}
