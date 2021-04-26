#include "../minishell.h"

void	ft_tochka_zapitaya(t_pars *len, char *line)
{
		len->flag = 0;
		len->i++;
}

void	ft_redirect(t_pars *len, char *line)
{
	len->flag = 0;
	if (line[len->i] == '>')
	{
		if (line[++len->i] == '>')
			len->i++;
	}
	else
	{
		if (line[++len->i] == '<')
			len->i++;
	}
}

int	ft_operator(t_pars *len, char *line)
{
	if (line[len->i] == '&')
	{
		if (line[++len->i] == '&')
		{
			len->i++;
			len->flag = 0;
			return 1;
		}
	}
	else
	{
		len->flag = 0;
		if (line[++len->i] == '|')
		{
			len->i++;
			return 1;
		}
		return 1;
	}
	return 0;
}

void	ft_len_alpha(char *line, t_pars *len, t_monna *lisa) // пропуск символов и ковычки (для счетчика слов)
{
	while (line[len->i] && line[len->i] != ' '
		&& line[len->i] != '\t' && line[len->i] != ';'
			&& line[len->i] != '&' && line[len->i] != '|'
				&& line[len->i] != '>' && line[len->i] != '<')
	{
		len->count = 0;
		if (line[len->i] == '\"')
			ft_len_kov_1(len, line, lisa); // работа с ковычками (счетчик слов)
		if (line[len->i] == '\'')
			ft_len_kov_2(len, line); // работа с ковычками (счетчик слов)
		if (line[len->i] == '\\') // работа с экранированием
			ft_ecran(line, len);
		if (line[len->i] == '$') // доллар $
			ft_kov_dollar(lisa, line, len);
		while (line[len->i] && line[len->i] != '\t' && line[len->i] != ' '
			&& line[len->i] != '\"' && line[len->i] != '\'' && line[len->i] != '\\'
				&& line[len->i] != ';' && line[len->i] != '&' && line[len->i] != '|'
					&& line[len->i] != '>' && line[len->i] != '<' && line[len->i] != '$')
		{
			len->i++;
			len->flag = 0; //флаг для счетчика слов
		}
	}
}

int	ft_len_words(char *line, t_monna *lisa) // считает колличество слов в строке из гнл с учетом ковычек
{
	t_pars	len;

	ft_bzero(&len, sizeof(t_pars));
	while (line[len.i])
	{
		len.flag = 1;
		if (line[len.i] == '\t' || line[len.i] == ' ') //пропуск пробелов и табуляции
			if (!(ft_len_space_tab(line, &len)))
					break ;
		if (line[len.i] == ';')
			ft_tochka_zapitaya(&len, line);
		if (line[len.i] == '|' || line[len.i] == '&')
		 	ft_operator(&len, line);
		if (line[len.i] == '<' || line[len.i] == '>')
		 	ft_redirect(&len, line);
		if (line[len.i] != '\t' && line[len.i] != ' ' && line[len.i] != ';'
			&& len.flag && line[len.i] != '&' && line[len.i] != '|'
				&& line[len.i] != '<' && line[len.i] != '>')
			ft_len_alpha(line, &len, lisa); // пропуск букв и работа с ковычками
		if (len.flag == 0)
			len.word++;
	}
	return (len.word);
}
