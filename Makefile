##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## compile the lib and basic rules
##

CC      = clang

CFLAGS  = -Iinclude -Wall -Wextra

LIB_SRC     = lib/my/my_putchar.c \
          lib/my/my_putnbr.c \
          lib/my/my_putnbr_unsigned.c \
          lib/my/my_putstr.c \
          lib/my/my_strlen.c \
          lib/my/my_printf.c \
          lib/my/my_putnbr_octal.c \
          lib/my/my_putnbr_hex.c \
          lib/my/my_put_pointer.c \
          lib/my/my_check_is_digit.c \
          lib/my/my_put_float.c \
          lib/my/process.c \
          lib/my/process_specifier.c \
		  lib/my/my_getnbr.c \
		  lib/my/my_str_to_word_array_no_strtok_r.c \
		  lib/my/my_strcpy.c \
		  lib/my/my_strdup.c \
		  lib/my/my_strcmp.c \
		  lib/my/my_strncmp.c \
		  lib/my/my_get_array_size.c \
		  lib/my/my_strcat.c \
		  lib/my/my_print_array.c \
		  lib/my/is_char_in_str.c
		

LIB_OBJ     = $(LIB_SRC:.c=.o)

LIB_NAME    = libmy.a

EXEC_NAME   = mysh

EXEC_SRC    = 	main.c \
				src/base_shell/main_loop.c \
				src/base_shell/parse_command.c \
				src/base_shell/exec_command.c \
				src/base_shell/find_cmd.c \
				src/builtins/base/check_builtins.c \
				src/builtins/base/builtin_env.c \
				src/builtins/base/builtin_exit.c \
				src/builtins/bonus/builtin_rick.c \
				src/builtins/bonus/builtin_boubou.c \
				src/builtins/bonus/builtin_help.c \
				src/pipes/pipes.c \
				src/pipes/pipe_utils.c \
				src/builtins/base/builtin_cd.c \
				src/redirections/redirections.c \
				src/redirections/redirection_utils.c

EXEC_OBJ	= $(SRC:.c=.o)

all: $(LIB_NAME) $(EXEC_NAME)

$(LIB_NAME): $(LIB_OBJ)
	ar rc $(LIB_NAME) $(LIB_OBJ)

$(EXEC_NAME): $(EXEC_OBJ)
	$(CC) -o $(EXEC_NAME) $(CFLAGS) $(EXEC_SRC) -L. -lmy
	@cat assets/boubou.txt

clean:
	rm -f $(LIB_OBJ)

fclean: clean
	rm -f $(LIB_NAME)
	rm -f $(EXEC_NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

debug: CFLAGS += -g
debug: all

.PHONY: all clean fclean re
