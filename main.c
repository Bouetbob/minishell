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

static char **dup_env(char **envp)
{
    int size = my_get_array_size(envp);
    char **env = malloc((size + 1) * sizeof(char *));

    if (!env)
        exit(84);
    for (int i = 0; i < size; i++)
        env[i] = my_strdup(envp[i]);
    env[size] = NULL;
    return env;
}

int main(UNUSED int ac, UNUSED char **av, char **envp)
{
    shell_t shell;

    signal(SIGINT, handle_sigint);
    shell.env = dup_env(envp);
    shell.status = 0;
    main_loop(&shell);
    return shell.status;
}
