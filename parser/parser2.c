#include "../minishell.h"

void	ft_ecran_pars(t_pars *pars, char *line, t_monna *lisa)
{
	if (line[++pars->i] != '\0' && line[pars->i] != '\t')
	{
		pars->flag = 0;
		lisa->tokens[pars->word][pars->j++] = line[pars->i++];
		lisa->flag_block_zvezda = 1; //если в слове был знак экрана то звезда не робит
		lisa->flag_block_operator = 1; //если в слове был знак экрана то оператов не робит
	}
}

void	ft_tochka_zapitaya_pars(t_pars *pars, char *line, t_monna *lisa)
{
	lisa->tokens[pars->word][pars->j++] = line[pars->i++];
	pars->flag = 0;
}

char *del_start_space(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_strdup(line);
	if (tmp == NULL)
			return (NULL);
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
	// a = ft_search_error(line);
	// if (line[0] == ';' || line[0] == '|' || line[0] == '&')
	// {
	// 	g_error = 1;
	// 	write(1, "syntax error near unexpected token\n", 35);
	// 	free(line);
	// 	return (NULL);
	// }
	return (line);
}
