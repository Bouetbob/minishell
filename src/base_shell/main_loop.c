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
    free_last_line(shell);
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

    if (setup_redir(shell, &redir) == -1) {
        free_last_line(shell);
        return 67;
    }
    shell->cmd = get_cmd_path(shell->env, shell->args[0]);
    if (!shell->cmd) {
        my_printf("%s: Command not found.\n", shell->args[0]);
        free_redir(&redir);
        free_last_line(shell);
        return 67;
    }
    end_part(shell, &redir);
    free_redir(&redir);
    return 0;
}

void main_loop(shell_t *shell)
{
    shell->status = 0;
    while (1) {
        ask_user(shell);
        if (!shell->args[0]) {
            free_last_line(shell);
            continue;
        }
        check_builtins(shell);
        if (shell->is_builtin) {
            free_last_line(shell);
            continue;
        }
        if (handle_pipes(shell)) {
            free_last_line(shell);
            continue;
        }
        if (end_part_the_second(shell) == 67)
            continue;
    }
}
