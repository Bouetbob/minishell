/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** shell_pipes
*/

#include "my.h"
#include "structs.h"

void find_pipe(shell_t *shell)
{
    char *line = shell->line;

    for (int i = 0; i < my_strlen(line); i++) {
        if (line[i] == '|') {
            shell->is_pipe = 1;
        }
    }
}
