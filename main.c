#include "minishell.h"
// int g_error; //на будущее, придумать где использовать глобальнуюю помимо ошибок

void	check_ctrl_backslash()
{
	write(0, "\b\b  \b\b", 6);
}

void	check_c()
{
	write(0, "\b\b  \b\b", 6);
	write(0, "\n", 1);
	write(0, "\033[33m ʕ ᵔᴥᵔ ʔ : \033[0m", 28);
	// echo $? = 1 //  а обычно 0
}

void    obrabotka_sig()
{
    signal(SIGINT, check_c);
	signal(SIGQUIT, check_ctrl_backslash);
}

int	main(int argc, char **argv, char **env)
{
	t_monna	lisa;
	t_pars	pars;
	char	*line;
	int i = 0;

	if (!(ft_init_all(&lisa, env)))
		return (0);
	ft_shell_lvl(argv, &lisa);
	while (lisa.status)
	{
		signal(SIGINT, obrabotka_sig);
 		signal(SIGQUIT, obrabotka_sig);
		write(1, "\033[33m", 5);
		line = readline("ʕ ᵔᴥᵔ ʔ : ");
		write(1, "\033[37m", 5);
		if (!line)
		{
			// lisa.status =  blabla (почистить память)
			write(0, "\b\b  \b\b", 6);
			write(1, "exit\n", 5);
			exit(0);
		}
		add_history(ft_strjoin(line, "\n"));
		line = del_start_space(line);
		if (line == NULL)
			continue;
		parser(line, &lisa, &pars); //парсим строку
		if (ft_search_syntax_error(&lisa, line))
			continue;
		ft_executor(&lisa); // выполнение , или после exit статус = 0
		free_all_1(line, &lisa);
	}
	free_all_2(line, &lisa);
	return (0);
}
