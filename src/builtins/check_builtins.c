/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** check_builtins
*/

#include "my.h"
#include <unistd.h>

void check_builtins(shell_t *shell)
{
    if (my_strcmp(shell->args[0], "exit") == 0) {
        builtin_exit(shell);
    }
    if (my_strcmp(shell->args[0], "env") == 0) {
        builtin_env(shell);
    }
    if (my_strcmp(shell->args[0], "rick") == 0) {
        rickroll(shell);
    }
    if (my_strcmp(shell->args[0], "best_boi") == 0) {
        builtin_boubou(shell);
    }
}
