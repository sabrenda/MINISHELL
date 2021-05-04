#include "../minishell.h"

int	ft_any_argument(t_monna *lisa, int *count)
{
	t_any	any;

	any.mas = ft_copy_massive(lisa, *count);
	any.pid = fork();
	if (any.pid == 0) // Дочерний процесс
	{
		any.str = ft_strjoin("/bin/", any.mas[0]);
		if (execve(any.str, any.mas, lisa->my_env) == -1)
			printf("minishell: %s: command not found\n", any.mas[0]);
		free (any.str);
		exit(EXIT_FAILURE);
	}
	else // Родительский процес
	{
		any.wpid = waitpid(any.pid, &any.status, WUNTRACED);
		while (!WIFEXITED(any.status) && !WIFSIGNALED(any.status))
			any.wpid = waitpid(any.pid, &any.status, WUNTRACED);
	}
	ft_free_mass(any.mas);
	any.mas = NULL;
	if (any.status == 256)
		any.status = 127;
	return (any.status);
}
