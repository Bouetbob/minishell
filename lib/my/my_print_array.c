/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** my_print_array
*/

#include "my.h"
#include <unistd.h>

void my_print_array(char **array)
{
    int i = 0;

    while (array[i]) {
        my_putstr(array[i]);
        write(1, "\n", 1);
        i++;
    }
}
