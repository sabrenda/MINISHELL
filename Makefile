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
			utils/davinci.c\
			utils/utils.c\
			executor/executor.c\

OBJS = $(SRCS:.c=.o)

GCC = clang

FLAGS = -Wall -Wextra -Werror

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
	norminette *.c
	norminette ./libft/*.c
	norminette *.h
	norminette ./libft/*.h

.PHONY:	all bonus clean fclean re norm run
