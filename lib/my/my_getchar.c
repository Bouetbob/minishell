/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** my_getchar
*/

#include <unistd.h>

int my_getchar(void)
{
    unsigned char c;

    if (read(0, &c, 1) == 1)
        return (int)c;
    return -1;
}
