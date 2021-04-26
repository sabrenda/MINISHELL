#include "../minishell.h"

int	ft_lenmassive(char **str) // счетчик строк в 2-ном массиве
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
