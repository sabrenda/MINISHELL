#include "../minishell.h"

void	ft_len_kov_1(t_pars *len, char *line) // ковычки " для счетчика слов
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
		// if (line[len->i] == '$')//-----------------надо звать лизу с енв--------------------
		// {

		// }
		if (line[len->i] == len->c) // если нашел вторую ковычку
		{
			len->i++; //пропуск ковычки
			if (len->count > 1)
				len->flag = 0; // флаг для счетчика слов
			break ;
		}
		if (line[len->i] && line[len->i] != '\\')
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
			if (line[++pars->i] == '\"' || line[pars->i] == '$')
				lisa->tokens[pars->word][pars->j++] = line[pars->i];
			else
				lisa->tokens[pars->word][pars->j++] = '\\';
			pars->i++;
			pars->count++;
		}
		// if (line[pars->i] == '$')//-----------------надо звать лизу с енв----------------
		// {

		// }
		if (line[pars->i] == pars->c) // если нашел вторую ковычку
		{
			pars->i++; // пропуск ковычки
			if (pars->count > 1)
				pars->flag = 0; //флаг для счетчика слов
			break ;
		}
		if (line[pars->i] && line[pars->i] != '\\')
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

void	ft_ecran(char *line, t_pars *len)
{
	if (line[++len->i] != '\0' && line[len->i] != '\t')// вывод экранного символа
	{
		len->i++;
		len->flag = 0;
	}
}

void	ft_len_alpha(char *line, t_pars *len) // пропуск символов и ковычки (для счетчика слов)
{
	while (line[len->i] && line[len->i] != ' '
		&& line[len->i] != '\t' && line[len->i] != ';'
			&& line[len->i] != '&' && line[len->i] != '|'
				&& line[len->i] != '>' && line[len->i] != '<')
	{
		len->count = 0;
		if (line[len->i] == '\"')
			ft_len_kov_1(len, line); // работа с ковычками (счетчик слов)
		if (line[len->i] == '\'')
			ft_len_kov_2(len, line); // работа с ковычками (счетчик слов)
		if (line[len->i] == '\\') // работа с экранированием
			ft_ecran(line, len);
		while (line[len->i] && line[len->i] != '\t' && line[len->i] != ' '
			&& line[len->i] != '\"' && line[len->i] != '\'' && line[len->i] != '\\'
				&& line[len->i] != ';' && line[len->i] != '&' && line[len->i] != '|'
					&& line[len->i] != '>' && line[len->i] != '<')
		{
			len->i++;
			len->flag = 0; //флаг для счетчика слов
		}
	}
}

void	ft_ecran_pars(t_pars *pars, char *line, t_monna *lisa)
{
	if (line[++pars->i] != '\0' && line[pars->i] != '\t')
	{
		if (line[pars->i] == '$')
			lisa->f_dollar = 1;
		pars->flag = 0;
		lisa->tokens[pars->word][pars->j++] = line[pars->i++];
	}
}

void	ft_len_alpha_pars(char *line, t_pars *pars, t_monna *lisa) //для добавляния символов,ковычки,экранирование
{
	while (line[pars->i] && (line[pars->i] != ' '
		&& line[pars->i] != '\t' && line[pars->i] != ';'
			&& line[pars->i] != '&' && line[pars->i] != '|'
				&& line[pars->i] != '>' && line[pars->i] != '<'))
	{
		if (line[pars->i] == '\"') // работа с ковычками ""
			ft_len_kov_pars_1(pars, line, lisa);
		if (line[pars->i] == '\'') // работа с ковычками '
			ft_len_kov_pars_2(pars, line, lisa);
		if (line[pars->i] == '\\') // работа с экранированием
			ft_ecran_pars(pars, line, lisa);
		while (line[pars->i] && line[pars->i] != ' ' && line[pars->i] != '\t'
			&& line[pars->i] != '\"' && line[pars->i] != '\''
				&& line[pars->i] != '\\' && line[pars->i] != ';'
					&& line[pars->i] != '&' && line[pars->i] != '|'
						&& line[pars->i] != '>' && line[pars->i] != '<')
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
