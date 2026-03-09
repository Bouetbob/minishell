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
    char **env;
    char **args;
} shell_t;

#endif /* !STRUCTS_H_ */
