NAME = minishell

SRCS = main.c\
			general/parser.c\
			general/parser_utils.c\
			general/utils.c\
			general/davinci.c

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
