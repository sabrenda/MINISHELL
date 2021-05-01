#include "../minishell.h"

void	free_all_1(char *line, t_monna *lisa)
{
	int	i;

	i = 0;
	free (line);
	while (lisa->tokens[i])
	{
		free (lisa->tokens[i]);
		i++;
	}
	free (lisa->tokens);
}

void	free_all_2(char *line, t_monna *lisa)
{
	int	i;

	i = 0;
	free (line);
	while (lisa->tokens[i])
	{
		free (lisa->tokens[i]);
		i++;
	}
	free (lisa->tokens);
	i = 0;
	while (lisa->my_env[i])
	{
		free (lisa->my_env[i]);
		i++;
	}
	free (lisa->my_env);
	if (lisa->tmp_env)
		free (lisa->tmp_env);
}
