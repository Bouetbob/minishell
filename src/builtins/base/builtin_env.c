/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** builtin_env
*/

#include "my.h"

void builtin_env(shell_t *shell)
{
    if (!shell->env) {
        my_printf("Error: no env to print");
        shell->status = 1;
        return;
    }
    my_print_array(shell->env);
    shell->status = 0;
    shell->is_builtin = 1;
}
