/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** builtin_exit
*/

#include "my.h"
#include <stdlib.h>

static int is_valid_number(char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] < '0' || str[i] > '9')
            return 0;
    return 1;
}

void builtin_exit(shell_t *shell)
{
    shell->is_builtin = 1;
    if (shell->args[1] && shell->args[2]) {
        my_printf("exit: Expression Syntax.\n");
        shell->status = 1;
        return;
    }
    if (shell->args[1] && !is_valid_number(shell->args[1])) {
        my_printf("exit: Expression Syntax.\n");
        shell->status = 1;
        return;
    }
    if (shell->args[1])
        shell->status = my_getnbr(shell->args[1]);
    my_printf("exit\n");
    free_last_line(shell);
    exit(shell->status);
}
