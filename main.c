#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"
#include "libft/get_next_line.h"

typedef struct	s_monna
{
	char	**commands;
	char	**my_env;
}				t_monna;

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

	i = -1;
	while (env[++i]);
	lisa.my_env = (char **)malloc(sizeof(char *) * i + 1);
	lisa.my_env[i] = NULL;
	i = -1;
	while (env[++i])
		lisa.my_env[i] = ft_strdup(env[i]);
	i = -1;
	status = 1;
	dir = ft_dir(lisa.my_env);
	while (status)
	{
		// ft_putstr_fd(" |^_^)-> ", 1);
		get_next_line(1, &line);
		printf("%s | (^_^)> %s\n", dir, line);
		// parser(line, &main);
		if (strcmp("fuck u", line) == 0)
		{
			free(line);
			break;
		}
		free(line);
		// executor(&liza, env);
	}
	i = -1;
	return (0);
}
