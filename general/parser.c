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
void	ft_redirect_pars(t_pars *len, t_monna *lisa, char *line)
{
	len->flag = 0;
	if (line[len->i] == '>')
	{
		lisa->tokens[len->word][len->j++] = line[len->i++];
		if (line[len->i] == '>')
			lisa->tokens[len->word][len->j++] = line[len->i++];
	}
	else
	{
		lisa->tokens[len->word][len->j++] = line[len->i++];
		if (line[len->i] == '<')
			lisa->tokens[len->word][len->j++] = line[len->i++];
	}
}
int	ft_len_words(char *line) // считает колличество слов в строке из гнл с учетом ковычек
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
			ft_len_alpha(line, &len); // пропуск букв и работа с ковычками
		if (len.flag == 0)
			len.word++;
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
void ft_operator_pars(t_pars *pars, char *line, t_monna *lisa)
{
	if (line[pars->i] == '&')
	{
		if (line[pars->i + 1] == '&')
		{
			lisa->tokens[pars->word][pars->j++] = line[pars->i++];
			lisa->tokens[pars->word][pars->j++] = line[pars->i++];
			pars->flag = 0;
			return ;
		}
		pars->i++;
	}
	else
	{
		pars->flag = 0;
		if (line[pars->i + 1] == '|')
		{
			lisa->tokens[pars->word][pars->j++] = line[pars->i++];
			lisa->tokens[pars->word][pars->j++] = line[pars->i++];
			return ;
		}
		lisa->tokens[pars->word][pars->j++] = line[pars->i++];
	}
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
			if (line[pars.i] != '\t' && line[pars.i] != ' ' && line[pars.i] != ';'
				&& line[pars.i] != '&' && line[pars.i] != '|')
				ft_len_alpha_pars(line, &pars, lisa); // добавляем символы, ковычки и экранирование
			if ((line[pars.i] == '|' || line[pars.i] == '&') && pars.flag)
		 		ft_operator_pars(&pars, line, lisa);
			if ((line[pars.i] == '<' || line[pars.i] == '>') && pars.flag)
		 		ft_redirect_pars(&pars, lisa, line);
			if (line[pars.i] == ';' && pars.flag)
			{
				lisa->tokens[pars.word][pars.j++] = line[pars.i++];
				break;
			}
		}
		lisa->tokens[pars.word][pars.j] = '\0';
	}
	return (1);
}
