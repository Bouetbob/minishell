/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** main
*/

#include "my.h"
#include "structs.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void handle_sigint(UNUSED int signal)
{
    write(1, "\n> ", 3);
}

int main(UNUSED int ac, UNUSED char **av, char **env)
{
    shell_t *shell = malloc(sizeof(shell_t));

    signal(SIGINT, handle_sigint);
    shell->env = env;
    main_loop(shell);
}
