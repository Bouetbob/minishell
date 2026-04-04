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
        return 1;
    shell->cmd = get_cmd_path(shell->env, shell->args[0]);
    if (!shell->cmd) {
        my_printf("%s: Command not found.\n", shell->args[0]);
        free_redir(&redir);
        return 1;
    }
    end_part(shell, &redir);
    free_redir(&redir);
    return 0;
}

static void run_segment(shell_t *shell, char **segment_args)
{
    char **old_args = shell->args;

    if (!segment_args || !segment_args[0])
        return;
    shell->args = segment_args;
    shell->is_builtin = 0;
    check_builtins(shell);
    if (shell->is_builtin || handle_pipes(shell)) {
        shell->args = old_args;
        return;
    }
    shell->status = end_part_the_second(shell);
    shell->args = old_args;
}

static void process_line_segments(shell_t *shell)
{
    int start = 0;

    if (!shell->args)
        return;
    for (int i = 0; shell->args[i]; i++) {
        if (my_strcmp(shell->args[i], ";") != 0)
            continue;
        shell->args[i] = NULL;
        run_segment(shell, &shell->args[start]);
        start = i + 1;
    }
    run_segment(shell, &shell->args[start]);
}

void main_loop(shell_t *shell)
{
    while (1) {
        my_printf("> ");
        shell->line = read_line();
        shell->args = split_line(shell->line, TOKEN_DELIMS);
        if (!shell->args) {
            free(shell->line);
            continue;
        }
        handle_quotes_args(shell->args);
        process_line_segments(shell);
        free_last_line(shell);
    }
}
