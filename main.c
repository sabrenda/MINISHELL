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
int g_error;

void	ft_len_razdel(char *line, t_pars *len) // пропуск символов и ковычки (для счетчика слов)
{
	while (line[len->i] && ((line[len->i] == '\"' || line[len->i] == '\'')
		|| (line[len->i] != ' ' && line[len->i] != '\t')))
	{
		len->count = 0;
		if (line[len->i] == '\"')
			ft_len_kov_1(len, line); // работа с ковычками (счетчик слов)
		if (line[len->i] == '\'')
			ft_len_kov_2(len, line); // работа с ковычками (счетчик слов)
		if (line[len->i] == '\\') // работа с экранированием
		{
			len->i++;
			if (line[len->i] == '\\' || line[len->i] == '\"' || line[len->i] == '\'' || line[len->i] == ';')
			{
				len->i++;
				len->flag = 0;
			}
		}
		while(line[len->i] != ' ' && line[len->i] != '\t' && line[len->i]
			&& line[len->i] != '\"' && line[len->i] != '\'' && line[len->i] != '\\')
		{
			len->i++;
			len->flag = 0; //флаг для счетчика слов
		}
	}
}

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
		line = del_start_space(line); // удаляю пробелы и табы в начале + (поиск ошибки при & |;)
		if (line == NULL)
			continue;
		// printf("%s\n", line);
		printf("words = %d\n", ft_len_words(line));
		// parser_token(line, lisa);
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
	return (0);
}
