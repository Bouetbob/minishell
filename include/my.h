/*
** EPITECH PROJECT, 2026
** my
** File description:
** header include :/
*/


#ifndef MY_H_
    #define MY_H_

    #include "structs.h"
    #include <stdint.h>
    #include <stdio.h>

    #define UNUSED [[maybe_unused]]
    #define READ_BUFSIZE 1024
    #define TOKEN_DELIMS " \t\r\n\a"
    #define TOK_BUFSIZE 64
    #define CD_BUFSIZE 1024

// for the lib
void my_putchar(char c);
int my_putnbr(int nb);
int my_putnbr_unsigned(unsigned int nb);
int my_putstr(char const *str);
int my_strlen(char const *str);
int process_specifier_simple(char specifier, va_list ap, int count);
int process_specifier_complex(char specifier, va_list ap, int count);
int my_printf(const char *format, ...);
int loop_while_my_printf(const char *format, int *i, va_list ap);
int my_putnbr_octal(unsigned int nb);
int my_putnbr_hex_lower(unsigned long nb);
int my_putnbr_hex_upper(unsigned long nb);
int process_flag(char flag);
int my_put_pointer(char *ptr);
int process_length(char *flag);
int loopcheck(const char *flag, int *i, va_list ap, int count);
int my_check_is_digit(char c);
int my_put_float(double nb);
int my_compute_float(int part_float, int count);
int my_getnbr(char *str);
char *my_strcpy(char *dest, char const *src);
char **my_stwa(char *str, const char *delims);
int my_strcmp(const char *str1, const char *str2);
int my_strncmp(const char *str1, const char *str2, uint64_t n);
int my_getchar(void);
char *my_strcat(char *dest, char const *src);
char *my_strdup(char const *src);
int my_get_array_size(char **array);
void my_print_array(char **array);
int is_char_in_str(char *str, char c);

// for the base shell
char **split_line(char *line, char *delims);
char *read_line(void);
int cmd_exec(char *cmd, char **args, char **env, redir_t *redir);
char **get_path(char **env);
char *get_cmd_path(char **env, char *cmd);
void free_last_line(shell_t *shell);
void main_loop(shell_t *shell);
char *read_line(void);
void handle_quotes_args(char **args);
char *preprocess_line(const char *line);

//for the pipes
int handle_pipes(shell_t *shell);
int pipe_check_helper(char **args, int i);
int is_valid_pipe(char **args);
int count_pipes(char **args);

//for redirections
int apply_redirections(redir_t *r);
int parse_redirections(char **args, redir_t *r);
int prepare_heredoc(redir_t *r);
int apply_redirections(redir_t *r);
void free_redir(redir_t *r);
int handle_token(char **args, int i, redir_t *r);
void shift_args(char **args, int i);
void init_redir(redir_t *r);
int is_redir(char *tok);
int parse_redirections(char **args, redir_t *r);
int is_delim(char *line, char *delim);

//for the builtins
void check_builtins(shell_t *shell);
void builtin_exit(shell_t *shell);
void builtin_env(shell_t *shell);
void rickroll(shell_t *shell);
void builtin_boubou(shell_t *shell);
void builtin_help(shell_t *shell);
void builtin_cd(shell_t *shell);

#endif
