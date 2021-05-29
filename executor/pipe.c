#include "../minishell.h"


void	ft_pipe_stdin(t_monna *lisa)
{
	dup2(lisa->fd_output, 1);
	dup2(lisa->fildes[0], 0);
	close(lisa->fildes[0]);
}

void	ft_pipe_stdout(t_monna *lisa)
{
	dup2(lisa->fildes[1], 1);
	close(lisa->fildes[1]);
}

void	ft_pipe_end(t_monna *lisa)
{
	dup2(lisa->fd_input, 0);
	lisa->flag_pipe = 0;
}

void	ft_pipe2(t_monna *lisa, int *count)
{
	if (lisa->flag_pipe == 1)
		ft_pipe_stdin(lisa);
	if (lisa->flag_pipe == 2)
		ft_pipe_end(lisa);
	if (lisa->tokens[*count] && !ft_strcmp(lisa->tokens[*count], "|"))
		*count += 1;
}

void	ft_pipe(t_monna *lisa, int i)
{
	while (lisa->tokens[i] && ft_operators(lisa->tokens[i]))
		i++;
	if (lisa->tokens[i] && (!ft_strcmp(lisa->tokens[i], "|") && lisa->tokens[i][2] == 0))
	{
		lisa->flag_pipe = 1;
		pipe(lisa->fildes);
		ft_pipe_stdout(lisa);
	}
	else
	{
		if (lisa->flag_pipe == 1)
			lisa->flag_pipe = 2;
		else
			lisa->flag_pipe = 0;
	}
}
