#include <string.h>
#include "libft/libft.h"
#include "libft/get_next_line.h"

typedef struct s_monna
{
	char	**commands;
	char	**my_env;
	char	**tokens;
	int		status;
}				t_monna;

int	ft_lenmassive(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	int		status;
	int		i;
	t_monna	lisa;

	lisa.my_env = (char **)malloc(sizeof(char *) * ft_lenmassive(env) + 1);
	lisa.my_env[ft_lenmassive(env)] = NULL;
	i = -1;
	while (env[++i])
		lisa.my_env[i] = ft_strdup(env[i]);
	i = -1;
	lisa.status = 1;
	while (lisa.status)
	{
		ft_putstr_fd("\033[31m༼ つ ◕_◕ ༽つ\033[32m$ ", 1);
		get_next_line(1, &line); //чтение ввода
		printf("%s\n", line);
		// parser(line, &lisa); //парсим строку
		if (strcmp("exit", line) == 0)
		{
			free(line);
			break;
		}
		free(line);
		// lisa.status = executor(&lisa, env); выполнение
	}
	return (0);
}
