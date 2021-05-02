#include "../minishell.h"

int	ft_env(t_monna *lisa, int *count) //енв
{
	int	i;

	i = 0;
	while (lisa->my_env[i])
	{
		ft_putendl_fd(lisa->my_env[i], 1);
		i++;
	}
	lisa->flag_command = 0;
	*count += 1;
	while (lisa->tokens[*count] && ft_operators(lisa->tokens[*count])) //пропускаем аргрументы если есть после env, так как по сабжу без них надо
		*count += 1;
	return (0);
}
