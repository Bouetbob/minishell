/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** is_char_in_str
*/

int is_char_in_str(char *str, char c)
{
    for (int i = 0; i < str[i]; i++) {
        if (str[i] == c)
            return 1;
    }
    return 0;
}
