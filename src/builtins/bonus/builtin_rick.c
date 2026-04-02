/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** builtin_rick
*/

#include "my.h"
#include <unistd.h>

void rickroll(shell_t *shell)
{
    char *args[] = {"/bin/curl", "ascii.live/rick", NULL};

    cmd_exec("/bin/curl", args, shell->env, NULL);
    shell->is_builtin = 1;
}
