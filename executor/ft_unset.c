#include "../minishell.h"

void	err_uns(t_monna *lisa, char *s)
{
	printf("Monnalisa: export: `%s': not a valid identifier\n", s);
}

int	delete_per(t_monna *lisa, char *str)
{
	t_unset	set;

	set.b = 0;
	set.i = 0;
	while (lisa->my_env[set.b])
		set.b++;
	set.new_mas = (char **)malloc(sizeof(char *) * (set.b));
	if (set.new_mas == 0)
		return (0);
	set.k = 0;
	while (lisa->my_env[set.i])
	{
		if (ft_strncmp(lisa->my_env[set.i], str, ft_strlen(str)) == 0)
		{
			set.i++;
			continue ;
		}
		set.new_mas[set.k] = ft_strdup(lisa->my_env[set.i]);
		set.i++;
		set.k++;
	}
	set.new_mas[set.k] = NULL;
	ft_free_mass(lisa->my_env);
	lisa->my_env = set.new_mas;
	return (1);
}

int	ft_unset(t_monna *lisa, int *count)
{
	*count += 1;
	if (!lisa->tokens[*count])
		return (0);
	if (srch_null_arg(*lisa->tokens[*count]) == 0
		|| ft_strchr(lisa->tokens[*count], '=') != NULL)
		err_uns(lisa, lisa->tokens[*count]);
	else
		delete_per(lisa, lisa->tokens[*count]);
	lisa->flag_command = 0;
	while (lisa->tokens[*count] && ft_operators_2(lisa->tokens[*count]))
		*count += 1;
	lisa->flag_error = 0;
	return (0);
}
