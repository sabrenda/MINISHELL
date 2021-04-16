#include "../minishell.h"

int	ft_len_words(char *line) // считает колличество слов в строке из гнл с учетом ковычек
{
	t_pars	len;

	ft_bzero(&len, sizeof(t_pars));
	while (line[len.i])
	{
		len.flag = 1;
		if (line[len.i] == '\t' || line[len.i] == ' ')
			if (!(ft_len_space_tab(line, &len))) //пропуск ковычек
					break ;
		if (line[len.i] != '\t' && line[len.i] != ' ')
			ft_len_alpha(line, &len); // пропуск букв и работа с ковычками
		if (len.flag == 0)
			len.word++;
		if (line[len.i] == '\0')
			break;
	}
	return (len.word);
}

int ft_memory_pars(t_monna *lisa, char *line, t_pars *pars)
{
	int	i;

	i = 0;
	lisa->tokens = (char **)malloc(sizeof(char *) * (ft_len_words(line) + 1));
	if (lisa->tokens == NULL)
		return (0);
	lisa->tokens[ft_len_words(line)] = NULL;
	while (i < ft_len_words(line))
	{
		lisa->tokens[i] = (char *)malloc(sizeof(char) * 1000);
		if (lisa->tokens[i] == NULL)
			return (0);
		i++;
	}
	if (ft_len_words(line) == 0) // если слов (символов) == 0
		lisa->tokens[i] = NULL;
	pars->i = 0;
	pars->word = -1;
	return (1);
}

int	parser(char *line, t_monna *lisa) //обрабтка строки из гнл
{
	t_pars	pars;

	if (ft_memory_pars(lisa, line, &pars) == 0)// выделяем память для двумерного массива
		return (0);
	while (++pars.word < ft_len_words(line) && line[pars.i])
	{
		pars.j = 0;
		pars.flag = 1;
		while (line[pars.i] && pars.flag)
		{
			if (line[pars.i] == '\t' || line[pars.i] == ' ')
				if (!(ft_len_space_tab(line, &pars))) //пропускаем space и табуляции
					break ;
			if (line[pars.i] != '\t' && line[pars.i] != ' ')
				ft_len_alpha_pars(line, &pars, lisa); // добавляем символы и работа с ковычками
		}
		lisa->tokens[pars.word][pars.j] = '\0';
	}
	return (1);
}
