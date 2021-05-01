#include "minishell.h"
// int g_error; //на будущее, придумать где использовать глобальнуюю помимо ошибок

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

int	ft_search_error(t_monna *lisa, char* line)
{
	int	flag_1;
	int	i;

	i = ft_err_1(lisa); // проверка на начало и повтор операторов
	// i = ft_err_2(lisa); // проверка на концовку операторов
	// i = ft_err_3(lisa); // проверка есть ли аргумент после редиректа
	if (i == 2)
	{
		write(1, "syntax error near unexpected token\n", 35);
		lisa->flag_error = 258;
		free_all_1(line, lisa);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	t_monna	lisa;
	t_pars	pars;
	char	*line;

	if (!(ft_init_all(&lisa, env)))
		return (0);
	while (lisa.status)
	{
		ft_putstr_fd("\033[31m༼ つ ◕_◕ ༽つ\033[32m$ ", 1);
		get_next_line(0, &line); //чтение ввода
		line = del_start_space(line); // удаляю пробелы и табы в начале + (поиск ошибки при << < > >> & |;)
		if (line == NULL)
			continue;
		// printf("words = %d\n", ft_len_words(line, &lisa)); // счетчик слов
		parser(line, &lisa, &pars); //парсим строку
		if (ft_search_error(&lisa, line))
			continue;
		i = 0;
		while (lisa.tokens[i])
		{
			ft_putstr_fd(lisa.tokens[i], 1);
			write(1, "\n", 1);
			i++;
		}
		// ft_executor(&lisa); // выполнение , после exit статус = 0
		free_all_1(line, &lisa);
	}
	free_all_2(line, &lisa);
	return (0);
}
