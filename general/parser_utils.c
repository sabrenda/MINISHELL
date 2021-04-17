#include "../minishell.h"

void	ft_len_kov(t_pars *len, char *line) // ковычки для счетчика слов
{
	len->count = 0;
	len->c = line[len->i++]; //копирую ковычку " или ' в char, и пропускаю эту ковычку
	while (1)
	{
		len->count++; //счетчик символов внутри ковычек
		if (len->c == '\"' && line[len->i] == '\\') //работа с экранированием
			if ((line[++len->i] == '\\' || line[len->i] == '\"') && len->count++)
				len->i++;
		if (line[len->i] == '\0') //если встретился \0 до ковычки, создаем вторую
		{
			line[len->i++] = len->c; //вместо \0 добавляем ковычку
			line[len->i] = '\0'; // добавляем конец строки
			if (len->count > 1)
				len->flag = 0; // флаг для счетчика слов
			break ;
		}
		if (line[len->i] == len->c) // если нашел вторую ковычку
		{
			len->i++; //пропуск ковычки
			if (len->count > 1)
				len->flag = 0; // флаг для счетчика слов
			break ;
		}
		len->i++; //пробегаемся по строке
	}
}

void	ft_len_kov_pars(t_pars *pars, char *line, t_monna *lisa) // ковычки парсер
{
	pars->count = 0;
	pars->c = line[pars->i++]; //копирую ковычку " или ' в char, и пропускаю эту ковычку
	while (1)
	{
		pars->count++; //счетчик символов внутри ковычек
		if (pars->c == '\"' && line[pars->i] == '\\') //работа с экранированием
		{
			pars->i++;
			if (line[pars->i] == '\"')
				lisa->tokens[pars->word][pars->j++] = line[pars->i++];
			else if (line[pars->i] != '\\')
				lisa->tokens[pars->word][pars->j++] = '\\';
			pars->count++;
		}
		if (line[pars->i] == pars->c) // если нашел вторую ковычку
		{
			pars->i++; // пропуск ковычки
			if (pars->count > 1)
				pars->flag = 0; //флаг для счетчика слов
			break ;
		}
		lisa->tokens[pars->word][pars->j++] = line[pars->i++]; //добавляет при нахождении символов
	}
}

void	ft_len_alpha(char *line, t_pars *len) // пропуск символов и ковычки (для счетчика слов)
{
	while (line[len->i] && ((line[len->i] == '\"' || line[len->i] == '\'')
		|| (line[len->i] != ' ' && line[len->i] != '\t')))
	{
		if (line[len->i] == '\"' || line[len->i] == '\'')
			ft_len_kov(len, line); // работа с ковычками (счетчик слов)
		if (line[len->i] == '\\') // работа с экранированием
		{
			len->i++;
			if (line[len->i] == '\\' || line[len->i] == '\"' || line[len->i] == '\'')
			{
				len->i++;
				len->flag = 0;
			}
		}
		while(line[len->i] != ' ' && line[len->i] != '\t' && line[len->i]
			&& line[len->i] != '\"' && line[len->i] != '\'' && line[len->i] != '\\')
		{
			if (line[len->i])
			len->i++;
			len->flag = 0; //флаг для счетчика слов
		}
	}
}

void	ft_len_alpha_pars(char *line, t_pars *pars, t_monna *lisa) //для добавляния символов,ковычки,экранирование
{
	while (line[pars->i] && (line[pars->i] != ' ' && line[pars->i] != '\t'))
	{
		if (line[pars->i] == '\"' || line[pars->i] == '\'')
			ft_len_kov_pars(pars, line, lisa); // работа с ковычками (парсер)
		if (line[pars->i] == '\\') // работа с экранированием
		{
			pars->i++;
			if (line[pars->i] == '\\' || line[pars->i] == '\"' || line[pars->i] == '\'')
			{
				lisa->tokens[pars->word][pars->j++] = line[pars->i++];
				pars->flag = 0;
			}
			else if (line[pars->i] == '$')
				lisa->f_dollar = 1;
		}
		while(line[pars->i] != ' ' && line[pars->i] != '\t' && line[pars->i]
			&& line[pars->i] != '\"' && line[pars->i] != '\'' && line[pars->i] != '\\')
		{
			lisa->tokens[pars->word][pars->j++] = line[pars->i++]; // добавляем в наш массив символы
			pars->flag = 0;
		}
	}
}

int	ft_len_space_tab(char *line, t_pars *len) //пропуск табов и спэйсов
{
	while (line[len->i] == '\t' || line[len->i] == ' ')
		len->i++;
	if (line[len->i] == '\0')
		return (0);
	return (1);
}
