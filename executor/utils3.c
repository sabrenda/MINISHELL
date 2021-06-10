#include "../minishell.h"

void	ft_tochka(t_monna *lisa, int *count)
{
	lisa->flag_red_files = 0;
	count += 1;
}

void	ft_else(t_monna *lisa, int *count)
{
	lisa->flag_command = ft_any_argument(lisa, count);
	lisa->flag_error = lisa->flag_command;
}
