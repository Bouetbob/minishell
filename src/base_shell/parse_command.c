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

char **split_line(char *line, char *delims)
{
    int position = 0;
    char **tokens = malloc(TOK_BUFSIZE * sizeof(char *));
    char *token;

    if (!tokens)
        exit(84);
    token = strtok(line, delims);
    while (token != NULL) {
        tokens[position] = token;
        position++;
        if (position >= TOK_BUFSIZE - 1) {
            tokens[position] = NULL;
            return tokens;
        }
        token = strtok(NULL, delims);
    }
    tokens[position] = NULL;
    return tokens;
}

static void handle_quotes(char *str)
{
    int i = 0;
    int j = 0;
    char quote = 0;

    while (str[i]) {
        if ((str[i] == '\'' || str[i] == '"') && !quote) {
            quote = str[i];
            i++;
            continue;
        }
        if (str[i] == quote) {
            quote = 0;
            i++;
            continue;
        }
        str[j] = str[i];
        i++;
        j++;
    }
    str[j] = '\0';
}

void handle_quotes_args(char **args)
{
    for (int i = 0; args[i]; i++)
        handle_quotes(args[i]);
}