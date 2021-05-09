#include "../minishell.h"

int	ft_env(t_monna *lisa, int *count) //енв
{
	int	i;

	i = 0;
	// ft_pipe(lisa, *count);
	// if (lisa->flag_pipe == 1)
	// 	ft_pipe_stdout(lisa);
	while (lisa->my_env[i])
	{
		if (strchr(lisa->my_env[i], 61))
			ft_putendl_fd(lisa->my_env[i], 1);
		i++;
	}
	// if (lisa->flag_pipe == 1)
	// 	ft_pipe_stdin(lisa);
	// if (lisa->flag_pipe == 2)
	// 	ft_pipe_end(lisa);
	lisa->flag_command = 0;
	*count += 1;
	while (lisa->tokens[*count] && ft_operators(lisa->tokens[*count]))
		*count += 1;
	lisa->flag_error = 0;
	return (0);
}
