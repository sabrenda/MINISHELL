#include "../minishell.h"

int	ft_search_com(char *str)
{
	if (!(ft_strcmp(str, "echo")) || !(ft_strcmp(str, "cd"))
		|| !(ft_strcmp(str, "pwd")) || !(ft_strcmp(str, "export"))
		|| !(ft_strcmp(str, "unset")) || !(ft_strcmp(str, "env"))
		|| !(ft_strcmp(str, "exit")))
		return (1);
	return (0);
}

int	ft_operators(char *str)
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

int	ft_operators_2(char *str)
{
	if ((!(strcmp(str, "&&")) && str[3] == 0)
		|| (!(strcmp(str, "||")) && str[3] == 0)
		|| (!(strcmp(str, "|")) && str[2] == 0)
		|| (!(strcmp(str, ";")) && str[2] == 0))
		return (0);
	return (1);
}

int	ft_red_serch(char *str)
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
