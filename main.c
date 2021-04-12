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
	{
		i++;
	}
	return (i);
}

char *ft_dir(char **myenv)
{
	int	i;
	int	j;
	int tmp;
	char *line;

	j = -1;
	i = -1;
	while(myenv[++i])
		if (strncmp("PWD=", myenv[i], 4) == 0)
			break;
	while (myenv[i][++j])
		if (myenv[i][j] == '/')
			tmp = j;
	j = 0;
	line = (char *)malloc(sizeof(char) * 1000);
	while (myenv[i][tmp])
	{
		line[j] = myenv[i][tmp];
		j++;
		tmp++;
	}
	line[j] = '\0';
	return (line);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	int		status;
	int		i;
	char	*dir;
	t_monna	lisa;

	i = ft_lenmassive(env);
	lisa.my_env = (char **)malloc(sizeof(char *) * i + 1);
	lisa.my_env[i] = NULL;
	i = -1;
	while (env[++i])
		lisa.my_env[i] = ft_strdup(env[i]);
	i = -1;
	lisa.status = 1;
	dir = ft_dir(lisa.my_env);
	while (lisa.status)
	{
		get_next_line(1, &line); //чтение ввода
		printf("%s | (^_^)> %s\n", dir, line);
		// parser(line, &lisa); //парсим строку
		if (strcmp("exit", line) == 0)
		{
			free(line);
			break;
		}
		free(line);
		// lisa.status = executor(&lisa, env); выполнение
	}
	i = -1;
	return (0);
}
