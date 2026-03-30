/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** builtin_cd
*/

#include "my.h"
#include "structs.h"
#include <unistd.h>
#include <dirent.h>

void builtin_cd(shell_t *shell)
{
    if (shell->args[1]) {
        if (chdir(shell->args[1]) == -1) {
            my_printf("%s: no such file or directory\n", shell->args[1]);
            shell->is_builtin = 1;
            shell->status = 1;
            return;
        }
        shell->is_builtin = 1;
        shell->status = 0;
    }
}
