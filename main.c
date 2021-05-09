#include "minishell.h"
// int g_error; //на будущее, придумать где использовать глобальнуюю помимо ошибок

int	main(int argc, char **argv, char **env)
{
	t_monna	lisa;
	t_pars	pars;
	char	*line;

	if (!(ft_init_all(&lisa, env)))
		return (0);
	ft_shell_lvl(argv, &lisa);
	while (lisa.status)
	{
		ft_putstr_fd("\033[0;1;41m༼ つ ◕_◕ ༽つ\033[0;32m$ ", 0);
		get_next_line(1, &line); //чтение ввода
		line = del_start_space(line); // удаляю пробелы и табы в начале + (поиск ошибки при << < > >> & |;)
		if (line == NULL)
			continue;
		// printf("words = %d\n", ft_len_words(line, &lisa)); // счетчик слов
		parser(line, &lisa, &pars); //парсим строку
		if (ft_search_syntax_error(&lisa, line))
			continue;
		ft_executor(&lisa); // выполнение , или после exit статус = 0
		free_all_1(line, &lisa);
	}
	free_all_2(line, &lisa);
	return (0);
}
