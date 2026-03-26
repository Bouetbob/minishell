/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** find_cmd
*/

#include "my.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char **get_path(char **env)
{
    char *temp = NULL;
    char **path = NULL;

    for (int i = 0; env[i]; i++) {
        if (my_strncmp("PATH", env[i], 4) == 0) {
            temp = my_strdup(env[i]);
            path = my_stwa(temp, ":=");
            free(temp);
            return path;
        }
    }
    return NULL;
}

char *get_cmd_path(char **env, char *cmd)
{
    char *temp = NULL;
    char **path = NULL;

    if (is_char_in_str(cmd, '/'))
        return my_strdup(cmd);
    path = get_path(env);
    if (!path)
        return NULL;
    for (int i = 1; path[i]; i++) {
        temp = malloc(my_strlen(path[i]) + my_strlen(cmd) + 2);
        my_strcpy(temp, path[i]);
        my_strcat(temp, "/");
        my_strcat(temp, cmd);
        if (access(temp, X_OK) == 0)
            return temp;
        free(temp);
    }
    return NULL;
}
