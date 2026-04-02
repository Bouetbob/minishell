/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** redirections
*/

#include "my.h"
#include "structs.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int handle_token(char **args, int i, redir_t *r)
{
    if (!args[i + 1]) {
        my_printf("Missing operand for %s\n", args[i]);
        return -1;
    }
    if (my_strcmp(args[i], "<") == 0)
        r->in_file = args[i + 1];
    if (my_strcmp(args[i], ">") == 0)
        r->out_file = args[i + 1];
    if (my_strcmp(args[i], ">>") == 0)
        r->out_file = args[i + 1];
    if (my_strcmp(args[i], ">>") == 0)
        r->append = 1;
    if (my_strcmp(args[i], "<<") == 0)
        r->heredoc_delim = args[i + 1];
    shift_args(args, i);
    shift_args(args, i);
    return 0;
}

static int heredoc_line(int fd, char *delim)
{
    char *line;

    my_printf("heredoc> ");
    line = read_line();
    if (is_delim(line, delim)) {
        free(line);
        return 1;
    }
    write(fd, line, my_strlen(line));
    free(line);
    return 0;
}

int prepare_heredoc(redir_t *r)
{
    int fds[2];

    if (pipe(fds) == -1) {
        perror("pipe");
        return -1;
    }
    while (!heredoc_line(fds[1], r->heredoc_delim))
        ;
    close(fds[1]);
    r->heredoc_fd = fds[0];
    return 0;
}

static int redir_stdin(redir_t *r)
{
    int fd =
        (r->heredoc_fd != -1) ? r->heredoc_fd : open(r->in_file, O_RDONLY);

    if (fd == -1) {
        my_printf("%s: No such file or directory\n", r->in_file);
        return -1;
    }
    if (dup2(fd, STDIN_FILENO) == -1) {
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

static int redir_stdout(redir_t *r)
{
    int flags = O_WRONLY | O_CREAT | (r->append ? O_APPEND : O_TRUNC);
    int fd = open(r->out_file, flags, 0644);

    if (fd == -1) {
        my_printf("%s: Cannot open file\n", r->out_file);
        return -1;
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

int apply_redirections(redir_t *r)
{
    if ((r->heredoc_fd != -1 || r->in_file) && redir_stdin(r) == -1)
        return -1;
    if (r->out_file && redir_stdout(r) == -1)
        return -1;
    return 0;
}

void free_redir(redir_t *r)
{
    if (r->heredoc_fd != -1)
        close(r->heredoc_fd);
}
