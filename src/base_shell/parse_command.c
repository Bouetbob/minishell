/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** parse_command
*/

#include "my.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int is_special(char c)
{
    return c == ';' || c == '|' || c == '>' || c == '<';
}

static int copy_special(const char *line, int i, char *out, int j)
{
    out[j] = ' ';
    j++;
    out[j] = line[i];
    j++;
    if ((line[i] == '>' || line[i] == '<') && line[i + 1] == line[i]) {
        out[j] = line[i + 1];
        j++;
    }
    out[j] = ' ';
    j++;
    return j;
}

static int preprocess_skip(const char *line, int i)
{
    if ((line[i] == '>' || line[i] == '<') && line[i + 1] == line[i])
        return 2;
    return 1;
}

char *preprocess_line(const char *line)
{
    int len = my_strlen(line);
    char *out = malloc(len * 3 + 2);
    int j = 0;

    if (!out)
        return NULL;
    for (int i = 0; line[i]; i++) {
        if (is_special(line[i])) {
            j = copy_special(line, i, out, j);
            i += preprocess_skip(line, i) - 1;
        } else {
            out[j] = line[i];
            j++;
        }
    }
    out[j] = '\0';
    return out;
}

char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1) {
        free(line);
        return NULL;
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
