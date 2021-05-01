#include "minishell.h"
int g_error; //на будущее, придумать где использовать глобальнуюю помимо ошибок

// void	ft_search_error(t_monna *lisa, char* line)
// {
// 	if (line[0] == ';' || line[0] == '|' || line[0] == '&')
// 	{
// 		g_error = 1;
// 		write(1, "syntax error near unexpected token\n", 35);
// 		free(line);
// 		return (NULL);
// 	}
// }

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
		// ft_search_error(&lisa, line);
		// printf("words = %d\n", ft_len_words(line, &lisa)); // счетчик слов
		parser(line, &lisa, &pars); //парсим строку
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
