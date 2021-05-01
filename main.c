#include "minishell.h"
int g_error; //на будущее, придумать где использовать глобальнуюю помимо ошибок

int	main(int argc, char **argv, char **env)
{
	t_monna	lisa;
	t_pars	pars;
	char	*line;
	int		i;

	ft_davinci();
	ft_bzero(&lisa, sizeof(t_monna));
	lisa.my_env = (char **)malloc(sizeof(char *) * ft_lenmassive(env) + 1);
	lisa.my_env[ft_lenmassive(env)] = NULL;
	lisa.tmp_env = (char *)malloc(sizeof(char *) * 300);

	i = 0;
	while (env[i])
	{
		lisa.my_env[i] = ft_strdup(env[i]);
		i++;
	}
	lisa.my_env[i] = NULL;
	lisa.status = 1;
	while (lisa.status)
	{
		ft_putstr_fd("\033[31m༼ つ ◕_◕ ༽つ\033[32m$ ", 1);
		get_next_line(0, &line); //чтение ввода
		line = del_start_space(line); // удаляю пробелы и табы в начале + (поиск ошибки при << < > >> & |;)
		if (line == NULL)
			continue;
		// printf("words = %d\n", ft_len_words(line, &lisa)); // счетчик слов
		parser(line, &lisa, &pars); //парсим строку
		// if (ft_search_error(&lisa))
		// {
		// 	ft_syntax_error();
		// }
		i = 0;
		while (lisa.tokens[i])
		{
			ft_putstr_fd(lisa.tokens[i], 1);
			write(1, "\n", 1);
			i++;
		}
		free(line);
		// ft_executor(&lisa); // выполнение , после exit статус = 0
	}
	return (0);
}
