#include "../minishell.h"

void	ft_free_mass(char	**mas)
{
	int	i = 0;

	while (mas[i])
		free (mas[i++]);
	free (mas);
}

char **ft_copy_massive(t_monna *lisa, int i)
{
	char	**str;
	int		j;
	int		tmp;

	tmp = i;
	j = 0;
	while (lisa->tokens[i] && ft_operators(lisa->tokens[i]))
	{
		i++;
		j++;
	}
	i = tmp;
	str = (char **)malloc(sizeof(char *) * (j + 2)); // добавить ее в лизу
	j = 0;
	ft_bzero(str, sizeof(char **));
	while (lisa->tokens[i] && ft_operators(lisa->tokens[i]))
	{
		str[j] = ft_strdup(lisa->tokens[i]);
		j++;
		i++;
	}
	str[j] = NULL;
	str[j + 1] = NULL;
	if (str[0] && !strncmp(str[0], "./minishell", 11)) // можно переделать на execve("/bin/ps", .., ..) и считать bash и ./minishell
	{
		if (str[1] == NULL)
		{
			str[1] = ft_strdup(ft_itoa(lisa->shell_lvl));
			str[2] = NULL;
		}
		else
		{
			free (str[1]);
			str[1] = ft_strdup(ft_itoa(lisa->shell_lvl));
		}
	}
	return (str);
}

int	ft_search_com(char *str) // является ли это комадой
{
	if (!(strcmp(str, "echo")) || !(strcmp(str, "cd")) || !(strcmp(str, "pwd"))
		|| !(strcmp(str, "export")) || !(strcmp(str, "unset"))
			|| !(strcmp(str, "env")) || !(strcmp(str, "exit")))
		return (1);
	return (0);
}

int	ft_operators(char *str) //проверяет является ли это оператором
{
	if ((!(strcmp(str, "&&")) && str[3] == 0)
		|| (!(strcmp(str, "||")) && str[3] == 0)
		|| (!(strcmp(str, "|")) && str[2] == 0)
		|| (!(strcmp(str, ">")) && str[2] == 0)
		|| (!(strcmp(str, "<")) && str[2] == 0)
		|| (!(strcmp(str, ">>")) && str[3] == 0)
		|| (!(strcmp(str, "<<")) && str[3] == 0)
		|| (!(strcmp(str, ";")) && str[2] == 0))
		return (0);
	return (1);
}

int	ft_operators_2(char *str) //проверяет является ли это оператором
{
	if ((!(strcmp(str, "&&")) && str[3] == 0)
		|| (!(strcmp(str, "||")) && str[3] == 0)
		|| (!(strcmp(str, "|")) && str[2] == 0)
		|| (!(strcmp(str, "<")) && str[2] == 0)
		|| (!(strcmp(str, ">")) && str[2] == 0)
		|| (!(strcmp(str, ">>")) && str[3] == 0)
		|| (!(strcmp(str, "<<")) && str[3] == 0)
		|| (!(strcmp(str, ";")) && str[2] == 0))
		return (0);
	return (1);
}
int	ft_red_serch(char *str) //проверяет является ли это редиректом
{
	if ((!(strcmp(str, ">")) && str[2] == 0)
		|| (!(strcmp(str, "<")) && str[2] == 0)
		|| (!(strcmp(str, ">>")) && str[3] == 0)
		|| (!(strcmp(str, "<<")) && str[3] == 0))
		return (1);
	return (0);
}

int	ft_red_serch_2(char *str)
{
	if ((!(strcmp(str, "&&")) && str[3] == 0)
		|| (!(strcmp(str, "|")) && str[2] == 0)
		|| (!(strcmp(str, "||")) && str[3] == 0)
		|| (!(strcmp(str, ";")) && str[2] == 0))
		return (1);
	return (0);
}
