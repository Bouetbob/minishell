/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** builtin_boubou
*/

#include "my.h"

void builtin_boubou(shell_t *shell)
{
    char *args[] = {"/bin/cat", "assets/boubou.txt", NULL};

    cmd_exec("/bin/cat", args, shell->env);
    shell->is_builtin = 1;
}