#include "../minishell.h"

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

int ft_memory_pars(t_monna *lisa, char *line, t_pars *pars)
{
	int	i;

	i = 0;
	lisa->tokens = (char **)malloc(sizeof(char *) * (ft_len_words(line, lisa) + 1));
	if (lisa->tokens == NULL)
		return (0);
	lisa->tokens[ft_len_words(line, lisa)] = NULL;
	while (i < ft_len_words(line, lisa))
	{
		lisa->tokens[i] = (char *)malloc(sizeof(char) * 1000);
		if (lisa->tokens[i] == NULL)
			return (0);
		i++;
	}
	if (ft_len_words(line, lisa) == 0) // если слов (символов) == 0
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
		if (line[pars->i] == '$')// работа с $
			ft_kov_dollar_pars(lisa, line, pars);
		if (line[pars->i] == '\\') // работа с экранированием
			ft_ecran_pars(pars, line, lisa);
		while (line[pars->i] && line[pars->i] != ' ' && line[pars->i] != '\t'
			&& line[pars->i] != '\"' && line[pars->i] != '\''
				&& line[pars->i] != '\\' && line[pars->i] != ';'
					&& line[pars->i] != '&' && line[pars->i] != '|'
						&& line[pars->i] != '>' && line[pars->i] != '<'
							&& line[pars->i] != '$')
		{
			lisa->tokens[pars->word][pars->j++] = line[pars->i++]; // добавляем в наш массив символы
			pars->flag = 0;
		}
	}
}

void ft_block_operator(t_monna *lisa, int nomer_ukaza)
{
	int i;

	i = 0;
	while (lisa->tokens[nomer_ukaza][i])
		i++;
	i++;
	if (lisa->flag_block_operator == 1)
		lisa->tokens[nomer_ukaza][i] = 1; // заблочить оператов
	else
		lisa->tokens[nomer_ukaza][i] = 0; // разрешить
}

int	parser(char *line, t_monna *lisa) //обрабтка строки из гнл
{
	t_pars	pars;

	if (ft_memory_pars(lisa, line, &pars) == 0)// выделяем память для двумерного массива
		return (0);
	while (++pars.word < ft_len_words(line, lisa) && line[pars.i])
	{
		pars.j = 0;
		pars.flag = 1;
		lisa->flag_block_zvezda = 0;
		lisa->flag_block_operator = 0;
		while (line[pars.i] && pars.flag)
		{
			if (line[pars.i] == '\t' || line[pars.i] == ' ')
				if (!(ft_len_space_tab(line, &pars))) //пропускаем space и табуляции
					break ;
			if (line[pars.i] != '\t' && line[pars.i] != ' ' && line[pars.i] != ';'
				&& line[pars.i] != '&' && line[pars.i] != '|')
				ft_len_alpha_pars(line, &pars, lisa); // добавляе символов,ковычки,экранирование,$
			if ((line[pars.i] == '|' || line[pars.i] == '&') && pars.flag)
				ft_operator_pars(&pars, line, lisa); // разделение операторов
			if ((line[pars.i] == '<' || line[pars.i] == '>') && pars.flag)
				ft_redirect_pars(&pars, lisa, line); // разделение редиректов
			if (line[pars.i] == ';' && pars.flag)
				ft_tochka_zapitaya_pars(&pars, line, lisa); // разделение ;
		}
		lisa->tokens[pars.word][pars.j] = '\0';
		if (!lisa->flag_block_zvezda)
			ft_zvezda_epta(lisa, pars.word);
		ft_block_operator(lisa, pars.word);
	}
	return (1);
}
