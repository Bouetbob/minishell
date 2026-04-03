/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** create_basic_shell
*/

#include "my.h"
#include "structs.h"
#include <stdlib.h>
#include <unistd.h>


void free_last_line(shell_t *shell)
{
    free(shell->line);
    free(shell->args);
}

static void ask_user(shell_t *shell)
{
    shell->is_builtin = 0;
    my_printf("> ");
    shell->line = read_line();
    shell->args = split_line(shell->line, TOKEN_DELIMS);
}

static void end_part(shell_t *shell, redir_t *redir)
{
    shell->status = cmd_exec(shell->cmd, shell->args, shell->env, redir);
    free(shell->cmd);
}

static int setup_redir(shell_t *shell, redir_t *redir)
{
    if (parse_redirections(shell->args, redir) == -1)
        return -1;
    if (redir->heredoc_delim && prepare_heredoc(redir) == -1)
        return -1;
    return 0;
}

static int end_part_the_second(shell_t *shell)
{
    redir_t redir;

    if (setup_redir(shell, &redir) == -1)
        return 67;
    shell->cmd = get_cmd_path(shell->env, shell->args[0]);
    if (!shell->cmd) {
        my_printf("%s: Command not found.\n", shell->args[0]);
        free_redir(&redir);
        return 67;
    }
    end_part(shell, &redir);
    free_redir(&redir);
    return 0;
}

static char ***split_semicolons(char **args)
{
    char ***segments = malloc(TOK_BUFSIZE * sizeof(char **));
    int seg = 0;
    int start = 0;

    if (!segments)
        exit(84);
    for (int i = 0; args[i]; i++) {
        if (my_strcmp(args[i], ";") != 0)
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

static void run_segment(shell_t *shell, char **args)
{
    shell->args = args;
    if (!shell->args[0])
        return;
    check_builtins(shell);
    if (shell->is_builtin)
        return;
    if (handle_pipes(shell))
        return;
    end_part_the_second(shell);
}

void main_loop(shell_t *shell)
{
    char ***segments;
    char **original_args;

    shell->status = 0;
    while (1) {
        ask_user(shell);
        original_args = shell->args;
        segments = split_semicolons(shell->args);
        for (int i = 0; segments[i]; i++) {
            shell->is_builtin = 0;
            run_segment(shell, segments[i]);
        }
        free(segments);
        shell->args = original_args;
        free_last_line(shell);
    }
}
