NAME = minishell

SRCS = main.c\
			parser/dollar.c\
			parser/kovichki.c\
			parser/parser_words.c\
			parser/parser_words2.c\
			parser/parser.c\
			parser/parser2.c\
			parser/utils.c\
			parser/zvezda.c\
			parser/zvezda2.c\
			parser/syntax_err.c\
			utils/davinci.c\
			utils/utils.c\
			utils/free.c\
			utils/shell_lvl.c\
			utils/init_all.c\
			executor/executor.c\
			executor/env.c\
			executor/any_argument.c\
			executor/ex_utils.c\
			executor/ft_pwd.c\
			executor/cd.c\
			executor/utils2.c\
			executor/ft_export.c\
			executor/ft_unset.c\
			executor/pipe.c\
			executor/ft_echo.c\

OBJS = $(SRCS:.c=.o)

GCC = clang

FLAGS = -g -Wall -Wextra -Werror

%.o: %.c
	$(GCC) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	clang $(FLAGS) -o $(NAME) $(OBJS) -L libft -lft

bonus: all

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C ./libft

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)

re: fclean all

run:
	./minishell

norm:
	norminette ./parser/*.c
	norminette ./executor/*.c
	norminette ./utils/*.c
	norminette ./libft/*.c
	norminette ./libft/*.h
	norminette *.h

.PHONY:	all bonus clean fclean re norm run
