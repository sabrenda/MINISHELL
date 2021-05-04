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

int search_arg(t_monna *lisa, int *count)
{
	if (!(lisa->tokens[*count]) || strcmp(lisa->tokens[*count], "&&") == 0
	|| strcmp(lisa->tokens[*count], "||") == 0
	|| strcmp(lisa->tokens[*count], "|") == 0
	|| strcmp(lisa->tokens[*count], ";") == 0)
		return 0;
	return 1;
}

char	*search_home(t_monna *lisa)
{
	int i;

	i = 0;
	while(lisa->my_env[i])
	{
		if (strncmp(lisa->my_env[i], "HOME=", 5) == 0)
		{
			printf("home - %s\n", strchr_boss(lisa->my_env[i], '='));

			return(strchr_boss(lisa->my_env[i], '=')); /// ft_strdup(strchr_boss(lisa->my_env[i], '='));
		}
		i++;
	}
	return (NULL);
}

void	go_change_pat_pwd(t_monna *lisa, char *s)  //cur_k станет oldpwd
{
	int i;

	i = 0;
	chdir(s);
	s = getcwd(NULL, 0);  // s наша сейчашняя pwd
	while (lisa->my_env[i])
	{
		if (strncmp(lisa->my_env[i], "PWD=", 4) == 0)
		{
			free(lisa->my_env[i]);
			lisa->my_env[i] = ft_strjoin("PWD=", s);
		}
		i++;
	}
}

void	change_oldpwd(t_monna *lisa, char *cur_k)
{
	int i;
	char *old;

	i = 0;
	while(lisa->my_env[i])
	{
		if (strncmp(lisa->my_env[i], "OLDPWD=", 7) == 0)
		{
			free(lisa->my_env[i]);
			lisa->my_env[i] = ft_strjoin("OLDPWD=", cur_k);
			return ;
		}
		i++;
	}
	ft_free_mass(lisa->my_env);
	old = ft_strjoin("OLDPWD=", cur_k);
	ft_copy_massive_env(lisa, old);
	// если не нахожу, то strjoin добавляю oldpwd в env
}

int	ft_cd(t_monna *lisa, int *count) //енв
{
	struct stat	status;
	char *s;
	char *cur_k;

	*count += 1;
	if (search_arg(lisa, count) == 0) // cd без параметров перемещает в $HOME и зависит от него
	{
		if(search_home(lisa) == NULL)
			printf("Monnalisa: cd: HOME not set\n");
		else
			chdir(search_home(lisa));
	}
	else if (chdir(lisa->tokens[*count]) == 0)// не
	{
		cur_k = getcwd(NULL, 0);
		s = ft_strdup(lisa->tokens[*count]); //
		go_change_pat_pwd(lisa, s);
		change_oldpwd(lisa, cur_k);
	}
	else
	{
		if ((chdir(lisa->tokens[*count])) == 0)
			printf("Monnalisa: cd: %s: No such file or directory\n", lisa->tokens[*count]);
		else if(stat(lisa->tokens[*count], &status) == 0)
			printf("Monnalisa: cd: %s: Not a directory\n", lisa->tokens[*count]);
	}
	lisa->flag_command = 0;
	*count += 1;
	while (lisa->tokens[*count] && ft_operators(lisa->tokens[*count])) //пропускаем аргрументы если есть после env, так как по сабжу без них надо
		*count += 1;
	lisa->flag_error = 0;
	return (0);
}
