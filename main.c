#include "minishell.h"

//void search(t_flag *fl, char *str)
//{
//	if (strcmp(str, "echo") == 0)
//		fl->f_echo = 1;
//	else if (strcmp(str, "cd") == 0)
//		fl->f_cd = 1;
//	else if (strcmp(str, "pwd") == 0)
//		fl->f_pwd = 1;
//	else if (strcmp(str, "export") == 0)
//		fl->f_export = 1;
//	else if (strcmp(str, "unset") == 0)
//		fl->f_unset = 1;
//	else if (strcmp(str, "env") == 0)
//		fl->f_env = 1;
//	else if (strcmp(str, "ls") == 0)
//		fl->f_exit = 1;
//	else if (strcmp(str, "exit") == 0)
//		fl->f_exit = 1;
//	else
//		fl->nothing = 1;
//}
int g_error; //на будущее, придумать где использовать глобальнуюю помимо ошибок

char *del_start_space(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_strdup(line);
	free (line);
	while (tmp[i] == ' ' || tmp[i] == '\t')
		i++;
	line = (char *)malloc(sizeof(char) * ft_strlen(tmp) + 1 - i);
	if (line == NULL)
		return NULL;
	while (tmp[i])
		line[j++] = tmp[i++];
	line[j] = tmp[i];
	free(tmp);
	if (line[0] == ';' || line[0] == '|' || line[0] == '&')
	{
		g_error = 1;
		write(1, "syntax error near unexpected token\n", 35);
		free(line);
		return (NULL);
	}
	return (line);
}

int	main(int argc, char **argv, char **env)
{
	t_monna	lisa;
	char	*line;
	int		status;
	int		i;
	int		tmp = 0;

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
		line = del_start_space(line); // удаляю пробелы и табы в начале + (поиск ошибки при & |;)
		if (line == NULL)
			continue;
		printf("words = %d\n", ft_len_words(line, &lisa)); // счетчик слов
		parser(line, &lisa); //парсим строку
		i = 0;
		// write(1, "tmp_env = ", 10); // ЕСЛИ ЗАХОЧЕШЬ ПОСМОТРЕТЬ ЧТО В СТРОКЕ где $ то раскоменти
		// ft_putstr_fd(lisa.tmp_env, 1);
		// write(1, "\n", 1);
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
		i = 0;
		if (strcmp("env", line) == 0)
		{
			while (lisa.my_env[i])
			{
				ft_putstr_fd(lisa.my_env[i], 1);
				write(1, "\n", 1);
				i++;
			}

		}
		free(line);
		// lisa.status = executor(&lisa, env); выполнение
	}
	return (0);
}
