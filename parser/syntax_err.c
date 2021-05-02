#include "../minishell.h"

int	ft_err_1(t_monna *lisa)
{
	int	flag_1;
	int	i;

	flag_1 = 0;
	i = -1;
	while (lisa->tokens[++i] && flag_1 != 2)
	{
		if (flag_1 == 0
			&& ((!strcmp(lisa->tokens[i], "&&") && lisa->tokens[i][3] == 0)
			|| (!strcmp(lisa->tokens[i], "||") && lisa->tokens[i][3] == 0)
			|| (!strcmp(lisa->tokens[i], "|") && lisa->tokens[i][2] == 0)
			|| (!strcmp(lisa->tokens[i], ";") && lisa->tokens[i][2] == 0)))
			flag_1 = 2;
		else if (flag_1 == 1
			&& ((!strcmp(lisa->tokens[i], "&&") && lisa->tokens[i][3] == 0)
			|| (!strcmp(lisa->tokens[i], "||") && lisa->tokens[i][3] == 0)
			|| (!strcmp(lisa->tokens[i], "|") && lisa->tokens[i][2] == 0)
			|| (!strcmp(lisa->tokens[i], ";") && lisa->tokens[i][2] == 0)))
			flag_1 = 0;
		else
			flag_1 = 1;
	}
	return (flag_1);
}

int	ft_err_2(t_monna *lisa)
{
	int	flag_1;
	int	i;

	flag_1 = 0;
	i = 0;
	while (lisa->tokens[i])
		i++;
	if (i == 0)
		return (flag_1);
	if ((!strcmp(lisa->tokens[i - 1], "&&") && lisa->tokens[i - 1][3] == 0)
		|| (!strcmp(lisa->tokens[i - 1], "||") && lisa->tokens[i - 1][3] == 0)
		|| (!strcmp(lisa->tokens[i - 1], "|") && lisa->tokens[i - 1][2] == 0)
		|| (!strcmp(lisa->tokens[i - 1], "<") && lisa->tokens[i - 1][2] == 0)
		|| (!strcmp(lisa->tokens[i - 1], "<<") && lisa->tokens[i - 1][3] == 0)
		|| (!strcmp(lisa->tokens[i - 1], ">") && lisa->tokens[i - 1][2] == 0)
		|| (!strcmp(lisa->tokens[i - 1], ">>") && lisa->tokens[i - 1][3] == 0))
	{
		flag_1 = 2;
		return (flag_1);
	}
	return (flag_1);
}

void	er3_init(t_er3 *er)
{
	er->flag = 0;
	er->i = -1;
}

int	ft_err_3(t_monna *lisa)
{
	t_er3	er;

	er3_init(&er);
	while (lisa->tokens[++er.i] && er.flag != 2)
	{
		if (er.flag == 0
			&& ((!strcmp(lisa->tokens[er.i], ">") && lisa->tokens[er.i][2] == 0)
			|| (!strcmp(lisa->tokens[er.i], "<") && lisa->tokens[er.i][2] == 0)
			|| (!strcmp(lisa->tokens[er.i], ">>") && lisa->tokens[er.i][3] == 0)
			|| (!strcmp(lisa->tokens[er.i], "<<") && lisa->tokens[er.i][3] == 0)))
			er.flag = 1;
		else if (er.flag == 1
			&& ((!strcmp(lisa->tokens[er.i], "&&") && lisa->tokens[er.i][3] == 0)
			|| (!strcmp(lisa->tokens[er.i], "||") && lisa->tokens[er.i][3] == 0)
			|| (!strcmp(lisa->tokens[er.i], "|") && lisa->tokens[er.i][2] == 0)
			|| (!strcmp(lisa->tokens[er.i], ";") && lisa->tokens[er.i][2] == 0)
			|| (!strcmp(lisa->tokens[er.i], ">") && lisa->tokens[er.i][2] == 0)
			|| (!strcmp(lisa->tokens[er.i], ">>") && lisa->tokens[er.i][3] == 0)
			|| (!strcmp(lisa->tokens[er.i], "<") && lisa->tokens[er.i][2] == 0)
			|| (!strcmp(lisa->tokens[er.i], "<<") && lisa->tokens[er.i][3] == 0)))
			er.flag = 2;
		else
			er.flag = 0;
	}
	return (er.flag);
}

int	ft_search_syntax_error(t_monna *lisa, char* line)
{
	int	flag_1;
	int	q;
	int	w;
	int	e;

	q = ft_err_1(lisa); // проверка на начало и повтор операторов
	w = ft_err_2(lisa); // проверка на концовку операторов
	e = ft_err_3(lisa); // проверка есть ли аргумент после редиректа
	if (q == 2 || w == 2 || e == 2)
	{
		write(1, "minishell: syntax error near unexpected token\n", 46);
		lisa->flag_error = 258;
		free_all_1(line, lisa);
		return (1);
	}
	return (0);
}
