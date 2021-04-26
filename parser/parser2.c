#include "../minishell.h"

void	ft_ecran_pars(t_pars *pars, char *line, t_monna *lisa)
{
	if (line[++pars->i] != '\0' && line[pars->i] != '\t')
	{
		pars->flag = 0;
		lisa->tokens[pars->word][pars->j++] = line[pars->i++];
	}
}

void	ft_tochka_zapitaya_pars(t_pars *pars, char *line, t_monna *lisa)
{
	lisa->tokens[pars->word][pars->j++] = line[pars->i++];
	pars->flag = 0;
}
