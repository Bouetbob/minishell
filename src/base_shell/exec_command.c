/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** exec_command
*/

#include "my.h"
#include "structs.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void redirection_part(redir_t *redir)
{
    if (redir && apply_redirections(redir) == -1)
        exit(1);
}

int cmd_exec(char *cmd, char **args, char **env, redir_t *redir)
{
    pid_t pid = fork();
    pid_t wpid;
    int status = 0;

    if (pid == -1)
        return 0;
    if (pid == 0) {
        signal(SIGINT, SIG_DFL);
        redirection_part(redir);
        if (execve(cmd, args, env) == -1)
            exit(84);
    }
    do {
        wpid = waitpid(pid, &status, WUNTRACED | WCONTINUED);
        if (wpid == -1) {
            perror("waitpid");
            exit(84);
        }
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    return 0;
}
