/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** builtin_exit
*/

#include "my.h"
#include <stdlib.h>

void builtin_exit(shell_t *shell)
{
    int code = my_getnbr(shell->args[1]);

    if (shell->args[1]) {
        shell->status = my_getnbr(shell->args[1]);
    }
    if (code == -1)
        shell->is_builtin = 1;
    free_last_line(shell);
    exit(shell->status);
}
