#include "../minishell.h"

void	ft_dollar_ili_net(t_monna *lisa, t_pars *len) //поиск в env нашего слова (счетчик слов)
{
	int	i;

	i = 0;
	while(lisa->my_env[i])
	{
		if (!(strncmp(lisa->tmp_env, lisa->my_env[i], ft_strlen(lisa->tmp_env))))
		{
			len->count++;
			len->flag = 0;
			return ;
		}
		i++;
	}
}

void	ft_dollar_ili_net_pars(t_monna *lisa, t_pars *pars) //поиск в env нашего слова (парсер)
{
	int	i;
	int	y;

	i = 0;
	while(lisa->my_env[i])
	{
		if (!(strncmp(lisa->tmp_env, lisa->my_env[i], ft_strlen(lisa->tmp_env))))
		{
			y = 0;
			while (lisa->my_env[i][y] != '=')
				y++;
			y++;
			while (lisa->my_env[i][y])
			{
				lisa->tokens[pars->word][pars->j] = lisa->my_env[i][y];
				pars->j++;
				y++;
				pars->flag = 0;
			}
			return ;
		}
		i++;
	}
}

void	ft_kov_dollar(t_monna *lisa, char *line, t_pars *len) // $ в ковычках (счетчик слов)
{
	int tmp = 0;

	tmp = 0;
	ft_clean_tmp_env(lisa);
	if (!(ft_isalnum(line[len->i + 1])) && line[len->i + 1] != '?')
	{
		len->i += 2;
		len->count++;
		len->flag = 0;
		return ;
	}
	if (proverka_isdigit(line, len))
		return ;
	if (line[len->i + 1] == '?')
	{
		len->i += 2;
		len->count++;
		len->flag = 0;
		return ;
	}
	while (ft_isalnum(line[++len->i]) || line[len->i] == '_')
		lisa->tmp_env[tmp++] = line[len->i];
	lisa->tmp_env[tmp] = '=';
	ft_dollar_ili_net(lisa, len);
}

void	ft_kov_dollar_pars(t_monna *lisa, char *line, t_pars *len) // $ в ковычках (парсер)
{
	char *str;
	int tmp = 0;
	int l = 0;
	tmp = 0;

	ft_clean_tmp_env(lisa);
	if (!(ft_isalnum(line[len->i + 1])) && line[len->i + 1] != '?')
	{
		lisa->tokens[len->word][len->j++] = line[len->i++];
		lisa->tokens[len->word][len->j++] = line[len->i++];
		len->flag = 0;
		return ;
	}
	if (proverka_isdigit(line, len))
		return ;
	if (line[len->i + 1] == '?') // добавляет вместо вопроса цифру с ошибки, можно atoi для большего числа
	{
		len->i++;
		str = ft_itoa(lisa->flag_error);
		while (str[l])
			lisa->tokens[len->word][len->j++] = str[l++];
		len->i++;
		len->flag = 0;
		return ;
	}
	while (ft_isalnum(line[++len->i]) || line[len->i] == '_')
		lisa->tmp_env[tmp++] = line[len->i];
	lisa->tmp_env[tmp] = '=';
	ft_dollar_ili_net_pars(lisa, len);
}
