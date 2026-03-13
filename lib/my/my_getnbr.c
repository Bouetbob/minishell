/*
** EPITECH PROJECT, 2026
** my get nbr
** File description:
** gets nbr
*/

#include "my.h"

int my_getnbr(char *str)
{
    int len = 0;
    int is_neg = 0;
    int result = 0;

    if (!str || my_strlen(str) == 0)
        return 0;
    len = my_strlen(str);
    is_neg = (str[0] == '-');
    if (is_neg && len == 1)
        return -1;
    for (int i = is_neg; i < len; i++) {
        if (str[i] < '0' || str[i] > '9')
            return -1;
        result = result * 10 + str[i] - '0';
    }
    if (is_neg)
        return -result;
    return result;
}
