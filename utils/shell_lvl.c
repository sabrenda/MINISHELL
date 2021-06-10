#include "../minishell.h"

void	ft_shell_if(t_monna *lisa, int u)
{
	lisa->shell_lvl = ft_atoi(lisa->my_env[u] + 6) + 1;
	free (lisa->my_env[u]);
	lisa->my_env[u] = ft_strjoin("SHLVL=", ft_itoa(lisa->shell_lvl));
}

void	ft_shell_else(t_monna *lisa, int u, char **argv)
{
		lisa->shell_lvl = ft_atoi(argv[1]) + 1;
		free (lisa->my_env[u]);
		lisa->my_env[u] = ft_strjoin("SHLVL=", ft_itoa(lisa->shell_lvl));
}

void	ft_shell_lvl(char **argv, t_monna *lisa)
{
	int	u;

	u = 0;
	if (!argv[1])
	{
		while (lisa->my_env[u])
		{
			if ((!ft_strncmp(lisa->my_env[u],"SHLVL=", 6)))
				ft_shell_if(lisa, u);
			u++;
		}
	}
	else
	{
		while (lisa->my_env[u])
		{
			if ((!ft_strncmp(lisa->my_env[u],"SHLVL=", 6)))
				ft_shell_else(lisa, u, argv);
			u++;
		}
	}
}
