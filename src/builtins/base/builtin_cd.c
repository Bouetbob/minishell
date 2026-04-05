/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** builtin_cd
*/

#include "my.h"
#include "structs.h"
#include <unistd.h>

static char *get_cd_target(shell_t *shell)
{
    char *home;

    if (shell->args[1])
        return shell->args[1];
    home = NULL;
    for (int i = 0; shell->env[i]; i++) {
        if (my_strncmp(shell->env[i], "HOME=", 5) == 0)
            home = shell->env[i] + 5;
    }
    return home;
}

void builtin_cd(shell_t *shell)
{
    char *target = get_cd_target(shell);

    shell->is_builtin = 1;
    if (!target) {
        my_printf("cd: HOME not set\n");
        shell->status = 1;
        return;
    }
    if (chdir(target) == -1) {
        my_printf("%s: no such file or directory\n", target);
        shell->status = 1;
        return;
    }
    shell->status = 0;
}
