/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** builtin_cd
*/

#include "my.h"
#include "structs.h"
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

static char *get_env_var(char **env, char *key)
{
    int len = my_strlen(key);

    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
            return env[i] + len + 1;
    }
    return NULL;
}

static void set_env_var(char **env, char *key, char *value)
{
    int len = my_strlen(key);
    char *newval;

    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], key, len) != 0 || env[i][len] != '=')
            continue;
        newval = malloc(len + my_strlen(value) + 2);
        my_strcpy(newval, key);
        my_strcat(newval, "=");
        my_strcat(newval, value);
        free(env[i]);
        env[i] = newval;
        return;
    }
}

void builtin_cd(shell_t *shell)
{
    char cwd[CD_BUFSIZE];
    char *prev;
    char *prev_dup;

    shell->is_builtin = 1;
    if (!shell->args[1])
        return;
    prev = get_env_var(shell->env, "PWD");
    prev_dup = prev ? my_strdup(prev) : NULL;
    if (chdir(shell->args[1]) == -1) {
        my_printf("%s: no such file or directory\n", shell->args[1]);
        free(prev_dup);
        shell->status = 1;
        return;
    }
    getcwd(cwd, sizeof(cwd));
    set_env_var(shell->env, "OLDPWD", prev_dup ? prev_dup : cwd);
    set_env_var(shell->env, "PWD", cwd);
    free(prev_dup);
    shell->status = 0;
}
