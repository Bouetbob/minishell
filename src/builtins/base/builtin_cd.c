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

static char *get_cd_target(shell_t *shell)
{
    if (shell->args[1])
        return shell->args[1];
    return get_env_var(shell->env, "HOME");
}

static void update_env_dirs(shell_t *shell, char *prev_dup, char *cwd)
{
    set_env_var(shell->env, "OLDPWD", prev_dup ? prev_dup : cwd);
    set_env_var(shell->env, "PWD", cwd);
    free(prev_dup);
    shell->status = 0;
}

void end_cd(char *cwd, shell_t *shell, char *prev_dup)
{
    getcwd(cwd, sizeof(cwd));
    update_env_dirs(shell, prev_dup, cwd);
}

void builtin_cd(shell_t *shell)
{
    char cwd[CD_BUFSIZE];
    char *prev;
    char *prev_dup;
    char *target = get_cd_target(shell);

    shell->is_builtin = 1;
    if (!target) {
        my_printf("cd: HOME not set\n");
        shell->status = 1;
        return;
    }
    prev = get_env_var(shell->env, "PWD");
    prev_dup = prev ? my_strdup(prev) : NULL;
    if (chdir(target) == -1) {
        my_printf("%s: no such file or directory\n", target);
        free(prev_dup);
        shell->status = 1;
        return;
    }
    end_cd(cwd, shell, prev_dup);
}
