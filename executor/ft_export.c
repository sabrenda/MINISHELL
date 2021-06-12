#include "../minishell.h"

void	keep_exp(t_monna *lisa, char *str)
{
	char	*new_s;
	int		i;
	int		check;

	check = 0;
	i = 0;
	new_s = ft_strjoin(str, "=");
	while (lisa->my_env[i])
	{
		if (ft_strcmp(lisa->my_env[i], str) == 0
			|| ft_strncmp(lisa->my_env[i], new_s, ft_strlen(new_s)) == 0)
			check = 1;
		i++;
	}
	if (check != 1)
		ft_copy_massive_env(lisa, str);
}

int	search_per_env(t_monna *lisa, char *str, int len)
{
	char	*new_s;
	int		i;

	i = 0;
	new_s = ft_strjoin(str, "=");
	while (lisa->my_env[i])
	{
		if (ft_strncmp(lisa->my_env[i], str, len) == 0
			|| ft_strncmp(lisa->my_env[i], str, len - 1) == 0)
		{
			free(lisa->my_env[i]);
			lisa->my_env[i] = ft_strdup(str);
			return (0);
		}
		i++;
	}
	return (1);
}

void	print_sort_env(t_monna *lisa)
{
	int	i;
	int	j;

	i = 0;
	while (lisa->my_env[i])
	{
		printf("declare -x ");
		if (strchr(lisa->my_env[i], 61) != NULL)
		{
			j = 0;
			while (lisa->my_env[i][j] != '=')
			{
				printf("%c", lisa->my_env[i][j]);
				j++;
			}
			printf("=");
			printf("\"%s\"\n", strchr_boss(lisa->my_env[i], '='));
		}
		else
			printf("%s\n", lisa->my_env[i]);
		i++;
	}
}

void	sort_env(t_monna *lisa)
{
	t_exp	ex;

	ex.i = 0;
	ex.s_i = 0;
	ex.len = 0;
	while (lisa->my_env[ex.len])
		ex.len++;
	while (ex.i < ex.len - 1)
	{
		ex.s_i = 0;
		while (ex.s_i < ex.len - 1)
		{
			if (ft_strcmp(lisa->my_env[ex.s_i], lisa->my_env[ex.s_i + 1]) > 0)
			{
				ex.temp = lisa->my_env[ex.s_i + 1];
				lisa->my_env[ex.s_i + 1] = lisa->my_env[ex.s_i];
				lisa->my_env[ex.s_i] = ex.temp;
			}
			ex.s_i++;
		}
		ex.i++;
	}
	print_sort_env(lisa);
}

int	ft_export(t_monna *l, int *i)
{
	int		t;
	char	*s;

	*i += 1;
	if (search_arg(l, i) == 0)
		sort_env(l);
	else if (tfy_ti_arg(l, l->tokens[*i]) == 2)
		err_exp(l, l->tokens[*i]);
	else
	{
		if (strchr(l->tokens[*i], 61) != NULL)
		{
			t = search_per_env(l, l->tokens[*i], len_arg(l->tokens[*i]));
			if (t == 1)
				ft_copy_massive_env(l, l->tokens[*i]);
		}
		else
			keep_exp(l, l->tokens[*i]);
	}
	l->flag_command = 0;
	while (l->tokens[*i] && ft_operators_2(l->tokens[*i]))
		*i += 1;
	l->flag_error = 0;
	return (0);
}
