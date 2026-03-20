/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** structs
*/

#ifndef STRUCTS_H_
    #define STRUCTS_H_

typedef struct shell_s {
    int status;
    int is_builtin;
    char *line;
    char *cmd;
    char **args;
    char **env;
} shell_t;

typedef struct pipe_util_s {
    int prev_read;
    int fds[2];
    int is_last;
    char **env;
} pipe_util_t;

#endif /* !STRUCTS_H_ */
