#include "../minishell.h"

int	ft_init_all(t_monna	*lisa, char **env)
{
	int	i;

	i = 0;
	ft_davinci();
	ft_bzero(lisa, sizeof(t_monna));
	lisa->my_env = (char **)malloc(sizeof(char *) * ft_lenmassive(env) + 1);
	if (!lisa->my_env)
		return (0);
	lisa->my_env[ft_lenmassive(env)] = NULL;
	lisa->tmp_env = (char *)malloc(sizeof(char *) * 300);
	if (!lisa->tmp_env)
		return (0);
	while (env[i])
	{
		lisa->my_env[i] = ft_strdup(env[i]);
		// if (!ft_strncmp(lisa->my_env[i],"SHLVL=", 6))
		// {
		// 	printf("env ==========  %d\n", g_shell_lvl);
		// 	if (g_shell_lvl == 0)
		// 		g_shell_lvl = ft_atoi(lisa->my_env[i]) + 1;
		// 	else
		// 		g_shell_lvl++;
		// 	printf("env ==========  %d\n", g_shell_lvl);
		// 	free (lisa->my_env[i]);
		// 	lisa->my_env[i] = ft_strjoin("SHLVL=", ft_itoa(g_shell_lvl));
		// }
		if (!(lisa->my_env[i]))
			return (0);
		i++;
	}
	lisa->my_env[i] = NULL;
	lisa->status = 1;
	return (1);
}
