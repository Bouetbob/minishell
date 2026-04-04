/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** find_cmd
*/

#include "my.h"
#include <stdlib.h>
#include <unistd.h>

static char *check_path_bin(char *path, char *cmd)
{
    char *temp = malloc(my_strlen(path) + my_strlen(cmd) + 2);

    if (!temp)
        return NULL;
    my_strcpy(temp, path);
    my_strcat(temp, "/");
    my_strcat(temp, cmd);
    if (access(temp, X_OK) == 0)
        return temp;
    free(temp);
    return NULL;
}

char **get_path(char **env)
{
    char *temp = NULL;
    char **path = NULL;

    for (int i = 0; env[i]; i++) {
        if (my_strncmp("PATH=", env[i], 5) == 0) {
            temp = my_strdup(env[i] + 5);
            path = split_line(temp, ":");
            free(temp);
            return path;
        }
    }
    return NULL;
}

char *get_cmd_path(char **env, char *cmd)
{
    char **path;
    char *res;

    if (!cmd) {
        return NULL;
    }
    if (is_char_in_str(cmd, '/')) {
        return (access(cmd, X_OK) == 0) ? my_strdup(cmd) : NULL;
    }
    path = get_path(env);
    if (!path) {
        return NULL;
    }
    for (int i = 0; path[i]; i++) {
        res = check_path_bin(path[i], cmd);
        if (res)
            return res;
    }
    return NULL;
}
