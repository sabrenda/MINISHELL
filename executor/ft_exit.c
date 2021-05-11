#include "../minishell.h"

void	err_num_arg(t_monna *lisa, char *str)
{
	printf("Monolisa: exit: %s: numeric argument required\n", str);
	lisa->flag_error = 255;
	exit(255);
}

int	boss_atoi(t_monna *lisa, int *count, const char *str)
{
	int			i;
	unsigned long	res;
	int b;

	i = 0;
	res = 0;
	b = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			b = -1;
		if(str[i] == '-' || str[i] == '+')
			err_num_arg(lisa, lisa->tokens[*count]);
	}
	if (str[i] == '-')
		b = -1;
	while (str[i] >= 48 && str[i] <= 57 && ft_isdigit(str[i]) == 1)
		res = res * 10 + (str[i++] - '0');
	if (res > 9223372036854775807 || str[i] == '+' || str[i] == '-' || ft_isdigit(str[i]) == 1)
		err_num_arg(lisa, lisa->tokens[*count]);
	return (res * b);
}

int	ft_lenstr(char **mas)
{
	int i;
	int i_c;
	char	*s;

	i = 0;
	i_c = 0;
	s = mas[1];
	while (mas[i])
	{
		i++;
		while (mas[1][i_c])
		{
			if (ft_isdigit(mas[1][i_c]) != 1)
				return (-1);
			i_c++;
		}
	}
	return (i);

}

int	err_many_arg(t_monna *lisa)
{
	printf("Monolisa: exit: too many arguments\n");
	lisa->flag_error = 1;
	return (0);
}

int	boss_isdigit(int c)
{
	if ((c >= 48 && c <= 57) || c == 43 || c == 45)
		return (1);
	return (0);
}


int	ft_exit(t_monna *lisa, int *count)
{
	int i;
	char **vika;

	i = 0;
	*count += 1;
	if (!lisa->tokens[*count])
		exit(EXIT_SUCCESS);
	vika = ft_copy_massive(lisa, *count);
	ft_putendl_fd("exit", 1);
	if (boss_isdigit(ft_lenstr(vika) == -1))
		err_num_arg(lisa, vika[*count]);
	else
		exit(boss_atoi(lisa, count, vika[*count]) % 256);
	while (lisa->tokens[*count] && ft_operators(lisa->tokens[*count]))
		*count += 1;
	lisa->flag_command = 0;
	lisa->flag_error = 0;
	return (0);
}
