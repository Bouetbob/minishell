/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** parse_command
*/

#include "my.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1) {
        if (errno == 0) {
            exit(0);
        } else {
            perror("readline");
            exit(1);
        }
    }
    return line;
}

char **split_line(char *line)
{
    int position = 0;
    char **tokens = malloc(TOK_BUFSIZE * sizeof(char *));
    char *token;

    if (!tokens)
        exit(84);
    token = strtok(line, TOKEN_DELIMS);
    while (token != NULL) {
        tokens[position] = token;
        position++;
        if (position >= TOK_BUFSIZE - 1) {
            tokens[position] = NULL;
            return tokens;
        }
        token = strtok(NULL, TOKEN_DELIMS);
    }
    tokens[position] = NULL;
    return tokens;
}
