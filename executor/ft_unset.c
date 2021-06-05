#include "../minishell.h"

void	err_uns(t_monna *lisa, char *s)
{
	printf("Monnalisa: export: `%s': not a valid identifier\n", s);
}

int	delete_per(t_monna *lisa, char *str)
{
	int		i;
	int		b;
	char	**new_mas;

	b = 0;
	i = 0;
	while(lisa->my_env[b])
		b++;
	new_mas = (char**)malloc(sizeof(char*) * (b)); // не вычитаю 1 , так как NULL
	if (new_mas == 0)
		return (0);
	int	k;
	k = 0;
	while(lisa->my_env[i])
	{
		if (ft_strncmp(lisa->my_env[i], str, ft_strlen(str)) == 0)
			i++;
		new_mas[k] = ft_strdup(lisa->my_env[i]);
		i++;
		k++;
	}
	new_mas[k] = NULL;
	ft_free_mass(lisa->my_env);
	lisa->my_env = new_mas;
	return (1);
}

int	ft_unset(t_monna *lisa, int *count)
{
	*count += 1;
	if ((ft_isalpha(*lisa->tokens[*count]) == 0 && ft_strcmp(lisa->tokens[*count], "_") != 0) || (strchr(lisa->tokens[*count], '=') != NULL))
		err_uns(lisa, lisa->tokens[*count]);
	else
		delete_per(lisa, lisa->tokens[*count]);
	lisa->flag_command = 0;
	while (lisa->tokens[*count] && ft_operators_2(lisa->tokens[*count])) //пропускаем аргрументы если есть после env, так как по сабжу без них надо
		*count += 1;
	lisa->flag_error = 0;
	return (0);
}
