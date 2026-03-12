/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** bultin_help
*/

#include "my.h"
#include "structs.h"

void builtin_help(shell_t *shell)
{
    my_putstr(
        "You asked for help ? Here's a small list of all the builtins in this "
        "shell :\n - env -> prints the current env with all its variables.\n - "
        "exit -> exits the shell with either the code you give it or the last "
        "exit code of a command.\n - best_boi -> reveals the secret of this "
        "universe.\n - rick -> do I really need to explain this one ?\n");
    shell->is_builtin = 1;
}
