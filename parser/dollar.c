#include "../minishell.h"

int	ft_dollar_ili_net(t_monna *lisa, t_pars *len) //поиск в env нашего слова (счетчик слов)
{
	int	i;

	i = 0;
	while(lisa->my_env[i])
	{
		if (!(strncmp(lisa->tmp_env, lisa->my_env[i], ft_strlen(lisa->tmp_env))))
			return (1);
		i++;
	}
	return (0);
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

	while (tmp < 300)
	{
		lisa->tmp_env[tmp] = '\0';
		tmp++;
	}
	tmp = 0;
	if (!(ft_isalnum(line[len->i + 1])) && line[len->i + 1] != '?')
	{
		len->i += 2;
		len->count++;
		len->flag = 0;
		return ;
	}
	if (ft_isdigit(line[len->i + 1]))
	{
		len->i += 2;
		return ;
	}
	if (line[len->i + 1] == '?')
	{
		len->i += 2;
		len->count++;
		len->flag = 0;
		return ;
	}
	len->i++;
	while (ft_isalnum(line[len->i]))
	{
		lisa->tmp_env[tmp] = line[len->i];
		len->i++;
		tmp++;
	}
	lisa->tmp_env[tmp++] = '=';
	lisa->tmp_env[tmp] = '\0';
	if (ft_dollar_ili_net(lisa, len))
	{
		len->count++;
		len->flag = 0;
	}
}

void	ft_kov_dollar_pars(t_monna *lisa, char *line, t_pars *pars) // $ в ковычках (парсер)
{
	int tmp = 0;

	while (tmp < 300)
	{
		lisa->tmp_env[tmp] = '\0';
		tmp++;
	}
	tmp = 0;
	if (!(ft_isalnum(line[pars->i + 1])) && line[pars->i + 1] != '?')
	{
		lisa->tokens[pars->word][pars->j++] = line[pars->i++];
		lisa->tokens[pars->word][pars->j++] = line[pars->i++];
		pars->flag = 0;
		return ;
	}
	if (ft_isdigit(line[pars->i + 1]))
	{
		pars->i += 2;
		return ;
	}
	if (line[pars->i + 1] == '?')
	{
		lisa->tokens[pars->word][pars->j++] = line[pars->i++];
		lisa->tokens[pars->word][pars->j++] = lisa->flag_error + 48;
		pars->i++;
		pars->flag = 0;
		return ;
	}
	while (ft_isalnum(line[++pars->i]))
		lisa->tmp_env[tmp++] = line[pars->i];
	lisa->tmp_env[tmp] = '=';
	ft_dollar_ili_net_pars(lisa, pars);
}
