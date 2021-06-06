#include "../minishell.h"

int	search_n(char *str)
{
	int	i;

	i =	0;
	if (strncmp("-n", str, 2) == 0)
	{
		while(str[++i])
		{
			if (str[i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

int	ft_echo(t_monna *lisa, int *count)
{
	int	new_i;

	*count += 1;
	new_i = 0;
	if (lisa->tokens[*count])
		new_i = search_n(lisa->tokens[*count]);
	while (lisa->tokens[*count] && ft_operators(lisa->tokens[*count]))
	{
		while (lisa->tokens[*count] && search_n(lisa->tokens[*count]) > 0)
			*count += 1;
		while (lisa->tokens[*count] && ft_operators(lisa->tokens[*count]))
		{
			ft_putstr_fd(lisa->tokens[*count], 1);
			if (lisa->tokens[*count + 1] && ft_operators(lisa->tokens[*count + 1]))
				write(1, " ", 1);
			*count += 1;
		}
	}
	if (new_i == 0)
		ft_putstr_fd("\n", 1);
	while (lisa->tokens[*count] && ft_operators_2(lisa->tokens[*count]))
		*count += 1;
	lisa->flag_command = 0;
	lisa->flag_error = 0;
	return (0);
}
