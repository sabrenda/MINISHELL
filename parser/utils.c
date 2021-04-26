#include "../minishell.h"

int	ft_len_space_tab(char *line, t_pars *len) //пропуск табов и спэйсов
{
	while (line[len->i] == '\t' || line[len->i] == ' ')
		len->i++;
	if (line[len->i] == '\0')
		return (0);
	return (1);
}
