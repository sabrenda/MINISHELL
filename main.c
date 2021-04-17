#include "minishell.h"

//void search(t_flag *fl, char *str)
//{
//	if (strcmp(str,"echo") == 0)
//		fl->f_echo = 1;
//	else if (strcmp(str,"cd") == 0)
//		fl->f_cd = 1;
//	else if (strcmp(str,"pwd") == 0)
//		fl->f_pwd = 1;
//	else if (strcmp(str,"export") == 0)
//		fl->f_export = 1;
//	else if (strcmp(str,"unset") == 0)
//		fl->f_unset = 1;
//	else if (strcmp(str,"env") == 0)
//		fl->f_env = 1;
//	else if (strcmp(str,"ls") == 0)
//		fl->f_exit = 1;
//	else if (strcmp(str,"exit") == 0)
//		fl->f_exit = 1;
//	else
//		fl->nothing = 1;
//}

int	main(int argc, char **argv, char **env)
{
	t_monna	lisa;
	char	*line;
	int		status;
	int		i;

	ft_davinci();
	lisa.f_dollar = 0;
	lisa.my_env = (char **)malloc(sizeof(char *) * ft_lenmassive(env) + 1);
	lisa.my_env[ft_lenmassive(env)] = NULL;
	i = -1;
	while (env[++i])
		lisa.my_env[i] = ft_strdup(env[i]);
	lisa.status = 1;
	while (lisa.status)
	{
		ft_putstr_fd("\033[31m༼ つ ◕_◕ ༽つ\033[32m$ ", 1);
		get_next_line(0, &line); //чтение ввода
		// printf("%s\n", line);
		printf("words = %d\n", ft_len_words(line));
		parser(line, &lisa); //парсим строку
		i = 0;
		while (lisa.tokens[i])
		{
			ft_putstr_fd(lisa.tokens[i], 1);
			write(1, "\n", 1);
			i++;
		}
		if (strcmp("exit", line) == 0)
		{
			free(line);
			break;
		}
		free(line);
		// lisa.status = executor(&lisa, env); выполнение
	}
	return (1);
}
