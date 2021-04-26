#include "../minishell.h"

void	ft_len_kov_1(t_pars *len, char *line, t_monna *lisa) // ковычки " для счетчика слов
{
	len->c = line[len->i++]; //копирую ковычку " или ' в char, и пропускаю эту ковычку
	while (1)
	{
		len->count++; //счетчик символов внутри ковычек
		if (line[len->i] == '\\') //работа с экранированием внутри ковычки "
			if ((line[++len->i] != '\0') && len->count++)
				len->i++;
		if (line[len->i] == '\0') //если встретился \0 до ковычки, создаем вторую
		{
			line[len->i++] = len->c; //вместо \0 добавляем ковычку
			line[len->i] = '\0'; // добавляем конец строки
			if (len->count > 1)
				len->flag = 0; // флаг для счетчика слов
			break ;
		}
		if (line[len->i] == '$')//-----------------надо звать лизу с енв--------------------
			ft_kov_dollar(lisa, line, len);
		if (line[len->i] == len->c) // если нашел вторую ковычку
		{
			len->i++; //пропуск ковычки
			if (len->count > 1)
				len->flag = 0; // флаг для счетчика слов
			break ;
		}
		if (line[len->i] && line[len->i] != '\\' && line[len->i] != '$')
			len->i++; //пробегаемся по строке
	}
}

void	ft_len_kov_2(t_pars *len, char *line) // ковычки '
{
	len->c = line[len->i++]; //копирую ковычку " или ' в char, и пропускаю эту ковычку
	while (1)
	{
		len->count++; //счетчик символов внутри ковычек
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
		if (line[len->i])
			len->i++; //пробегаемся по строке
	}
}

void	ft_len_kov_pars_1(t_pars *pars, char *line, t_monna *lisa) // ковычки парсер ""
{
	pars->count = 0;
	pars->c = line[pars->i++]; //копирую ковычку " или ' в char, и пропускаю эту ковычку
	while (1)
	{
		pars->count++; //счетчик символов внутри ковычек
		if (line[pars->i] == '\\') //работа с экранированием
		{
			if (line[pars->i + 1] == '\"' || line[pars->i + 1] == '$')
			{
				lisa->tokens[pars->word][pars->j++] = line[++pars->i];
				pars->i++;
			}
			else
				lisa->tokens[pars->word][pars->j++] = line[pars->i++];
			if (line[pars->i] == '\\')
				pars->i++;
			pars->count++;
		}
		if (line[pars->i] == '$')//-----------------надо звать лизу с енв----------------
			ft_kov_dollar_pars(lisa, line, pars);
		if (line[pars->i] == pars->c) // если нашел вторую ковычку
		{
			pars->i++; // пропуск ковычки
			if (pars->count > 1)
				pars->flag = 0; //флаг для счетчика слов
			break ;
		}
		if (line[pars->i] && line[pars->i] != '\\' && line[pars->i] != '$')
			lisa->tokens[pars->word][pars->j++] = line[pars->i++]; //добавляет при нахождении символов
	}
}

void	ft_len_kov_pars_2(t_pars *pars, char *line, t_monna *lisa) // ковычки парсер '
{
	pars->count = 0;
	pars->c = line[pars->i++]; //копирую ковычку " или ' в char, и пропускаю эту ковычку
	while (1)
	{
		pars->count++; //счетчик символов внутри ковычек
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
