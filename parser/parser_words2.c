#include "../minishell.h"

void	ft_ecran(char *line, t_pars *len)
{
	if (line[++len->i] != '\0' && line[len->i] != '\t')// вывод экранного символа
	{
		len->i++;
		len->flag = 0;
	}
}
