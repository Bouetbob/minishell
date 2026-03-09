/*
** EPITECH PROJECT, 2026
** my_putchar.c
** File description:
** put caracter
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}
