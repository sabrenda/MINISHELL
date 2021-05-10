#include "../minishell.h"

char	*strchr_boss(const char *s, int c)
{
	int	a;

	a = 0;
	if (c == '\0')
	{
		while (s[a] != '\0')
			a++;
		return ((char *)&s[a]);
	}
	while (s[a] != '\0')
	{
		if (s[a] == c)
		{
			a++;
			return ((char *)&s[a]);
		}
		a++;
	}
	return (0);
}

int	ft_copy_massive_env(t_monna *lisa, char *tmp)
{
	char	**str;
	int		j;
	int		i;

	i = 0;
	while (lisa->my_env[i])
		i++;
	str = (char **)malloc(sizeof(char *) * (i + 2));
	if (str == 0)
		return (0);
	i = 0;
	while (lisa->my_env[i])
	{
		str[i] = ft_strdup(lisa->my_env[i]);
		if (str[i] == 0)
			return (0);
		i++;
	}
	str[i] = ft_strdup(tmp);
	if (str[i] == 0)
		return (0);
	str[++i] = NULL;
	ft_free_mass(lisa->my_env);
	lisa->my_env = str;
	return (1);
}

int	search_arg(t_monna *lisa, int *count)
{
	if (!(lisa->tokens[*count])
		|| (!strcmp(lisa->tokens[*count], "&&") && lisa->tokens[*count][3] == 0)
		|| (!strcmp(lisa->tokens[*count], "||") && lisa->tokens[*count][3] == 0)
		|| (!strcmp(lisa->tokens[*count], "|") && lisa->tokens[*count][2] == 0)
		|| (!strcmp(lisa->tokens[*count], ";") && lisa->tokens[*count][2] == 0))
		return 0;
	return 1;
}
