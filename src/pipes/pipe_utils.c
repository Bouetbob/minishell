/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** pipe_utils
*/

#include "my.h"

int pipe_check_helper(char **args, int i)
{
    if (my_strcmp(args[i], "|") == 0) {
        if (!args[i + 1] || my_strcmp(args[i + 1], "|") == 0) {
            my_printf("Invalid null command.\n");
            return 1;
        }
    }
    return 0;
}

int is_valid_pipe(char **args)
{
    if (my_strcmp(args[0], "|") == 0) {
        my_printf("Invalid null command.\n");
        return 0;
    }
    for (int i = 0; args[i]; i++) {
        if (pipe_check_helper(args, i))
            return 0;
    }
    return 1;
}

int count_pipes(char **args)
{
    int count = 0;

    for (int i = 0; args[i]; i++)
        if (my_strcmp(args[i], "|") == 0)
            count++;
    return count;
}
