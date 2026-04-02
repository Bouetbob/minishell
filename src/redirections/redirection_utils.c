/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** redirection_utils
*/

#include "structs.h"
#include "my.h"

void shift_args(char **args, int i)
{
    while (args[i]) {
        args[i] = args[i + 1];
        i++;
    }
}

void init_redir(redir_t *r)
{
    r->in_file = NULL;
    r->out_file = NULL;
    r->heredoc_delim = NULL;
    r->heredoc_fd = -1;
    r->append = 0;
}

int is_redir(char *tok)
{
    if (!tok)
        return 0;
    return my_strcmp(tok, "<") == 0 || my_strcmp(tok, ">") == 0
        || my_strcmp(tok, ">>") == 0 || my_strcmp(tok, "<<") == 0;
}

int parse_redirections(char **args, redir_t *r)
{
    init_redir(r);
    for (int i = 0; args[i]; i++) {
        if (!is_redir(args[i]))
            continue;
        if (handle_token(args, i, r) == -1)
            return -1;
        i--;
    }
    return 0;
}

int is_delim(char *line, char *delim)
{
    int len = my_strlen(line);

    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    return my_strcmp(line, delim) == 0;
}
