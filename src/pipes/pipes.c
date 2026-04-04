/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** pipes
*/

#include "my.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char ***split_pipes(char **args, int n_pipes)
{
    char ***segments = malloc((n_pipes + 2) * sizeof(char **));
    int seg = 0;
    int start = 0;

    if (!segments)
        return NULL;
    for (int i = 0; args[i]; i++) {
        if (my_strcmp(args[i], "|") != 0)
            continue;
        args[i] = NULL;
        segments[seg] = &args[start];
        seg++;
        start = i + 1;
    }
    segments[seg] = &args[start];
    seg++;
    segments[seg] = NULL;
    return segments;
}

static void child_setup_io(pipe_util_t *pipe_util)
{
    if (pipe_util->prev_read != -1) {
        dup2(pipe_util->prev_read, STDIN_FILENO);
        close(pipe_util->prev_read);
    }
    if (!pipe_util->is_last) {
        dup2(pipe_util->fds[1], STDOUT_FILENO);
        close(pipe_util->fds[1]);
    }
}

static void child_exec(char **segment, char **env)
{
    redir_t redir;
    char *cmd;

    if (parse_redirections(segment, &redir) == -1)
        exit(1);
    if (redir.heredoc_delim && prepare_heredoc(&redir) == -1)
        exit(1);
    if (apply_redirections(&redir) == -1)
        exit(1);
    cmd = get_cmd_path(env, segment[0]);
    if (!cmd) {
        my_printf("%s: Command not found.\n", segment[0]);
        exit(127);
    }
    execve(cmd, segment, env);
    exit(84);
}

static void run_child(char **segment, pipe_util_t *pipe_util)
{
    pid_t pid = fork();

    if (pid == -1)
        return;
    if (pid == 0) {
        signal(SIGINT, SIG_DFL);
        if (!pipe_util->is_last)
            close(pipe_util->fds[0]);
        child_setup_io(pipe_util);
        if (!pipe_util->is_last)
            close(pipe_util->fds[1]);
        child_exec(segment, pipe_util->env);
    }
}

static void next_part(pipe_util_t *pipe_util)
{
    if (pipe_util->prev_read != -1)
        close(pipe_util->prev_read);
    if (pipe_util->is_last) {
        pipe_util->prev_read = -1;
        return;
    }
    close(pipe_util->fds[1]);
    pipe_util->prev_read = pipe_util->fds[0];
}

static int count_segments(char ***segments)
{
    int n = 0;

    while (segments[n])
        n++;
    return n;
}

static void run_pipeline(char ***segments, char **env)
{
    int n = count_segments(segments);
    pipe_util_t pipe_util = {.prev_read = -1, .env = env};

    for (int i = 0; i < n; i++) {
        pipe_util.is_last = (i == n - 1);
        if (!pipe_util.is_last)
            pipe(pipe_util.fds);
        run_child(segments[i], &pipe_util);
        next_part(&pipe_util);
    }
    while (wait(NULL) > 0)
        ;
}

int handle_pipes(shell_t *shell)
{
    int n_pipes = count_pipes(shell->args);
    char ***segments = NULL;

    if (n_pipes == 0)
        return 0;
    segments = split_pipes(shell->args, n_pipes);
    run_pipeline(segments, shell->env);
    free(segments);
    return 1;
}
