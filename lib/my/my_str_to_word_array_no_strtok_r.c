/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** my_str_to_word_array_no_strtok_r
*/

#include "my.h"
#include <stdlib.h>
#include <string.h>

char **my_stwa(char *str, const char *delims)
{
    char **result = malloc(sizeof(char *) * 256);
    char *temp = strtok(str, delims);
    int count = 0;

    while (temp != NULL) {
        result[count] = my_strdup(temp);
        count++;
        temp = strtok(NULL, delims);
    }
    result[count] = NULL;
    return result;
}
