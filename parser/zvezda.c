#include "../minishell.h"

int	ft_zvezda_konec(char *str, char *dir_name, int *flag)
{
	int	i;

	i = *flag;
	// **mba или **mb*** *am*a* *am*****b****
	while (str[i] == '*')
		i++;
	if (ft_zvezda_konec_2(i, str ,dir_name))
		return (1);
	return (0);
}

int	ft_zvezda_seredina(char *str, char *dir_name, int *flag)
{
	int	i;
	int	j;

	i = *flag;
	j = 0;
	// **mba или **mb*** *am*a* *am*****b****
	while (str[i] == '*')
		i++;
	while (str[i] != '*' && str[i] != '\0')
	{
		i++;
		if (str[i] == '*')
			j++;
	}
	if (j == 0)
		return (2);
	while (str[*flag] == '*')
		*flag += 1;
	if (ft_zvezda_seredina_2(str ,dir_name, flag))
		return (1);
	return (0);
}

int	ft_zvezda_nachalo(char *str, char *dir_name, int *flag)
{
	int	j;

	j = 0;
	// lam** или l**am*** l*amba* l*a*ba* l*mba
	while (str[*flag] != '*')
		*flag += 1;
	if (ft_zvezda_nachalo_2(*flag, str ,dir_name))
		return (1);
	return (0);
}

int	ft_zvezda_v_shoke(char *str, char *dir_name)
{
	int	j;
	int	flag;
	int	a;

	flag = 0;
	if (str[flag] && str[flag] != '*') //проверка начала lam** или l**am*** l*amba* l*a*ba* l*mba
	{
		a = ft_zvezda_nachalo(str, dir_name, &flag);
		if (a == 0)
			return (0);
	}
	if (str[flag] == '*') // проверка середины **am*** *a*a*
	{
		while (1)
		{
			a = ft_zvezda_seredina(str, dir_name, &flag);
			if (a == 0)
				return (0);
			if (a == 2)
				break ;
		}
	}
	if (str[flag] == '*' && str[ft_strlen(str) - 1] != '*') //проверка концовки **mba или **mb *am*a
	{
		a = ft_zvezda_konec(str, dir_name, &flag);
		if (a == 0)
			return (0);
	}
	return (1);
}

void	ft_zvezda_epta(t_monna *lisa, int nomer_ukaza)
{
	DIR	*mydir;
	struct	dirent *myfile;
	struct	stat mystat;
	int	i;
	int	count;
	int	x;
	int	j;

	count = 0;
	i = 0;
	j = 0;
	ft_clean_tmp_env(lisa);
	ft_strcopy(lisa->tmp_env, lisa->tokens[nomer_ukaza]);
	while (lisa->tmp_env[i])
	{
		if (lisa->tmp_env[i] == '*')
			count++;
		i++;
	}
	if (count == 0)
		return ;
	mydir = opendir(".");
	if (i == count)
	{
		while((myfile = readdir(mydir)) != NULL)
		{
			x = 0;
			stat(myfile->d_name, &mystat);
			if (myfile->d_name[0] == '.')
				continue ;
			while (myfile->d_name[x])
				lisa->tokens[nomer_ukaza][j++] = myfile->d_name[x++];
			lisa->tokens[nomer_ukaza][j++] = ' ';
		}
		lisa->tokens[nomer_ukaza][j - 1] = '\0';
		closedir(mydir);
		return ;
	}
	count = 0;
	while((myfile = readdir(mydir)) != NULL)
	{
		x = 0;
		stat(myfile->d_name, &mystat);
		if (myfile->d_name[0] == '.')
			continue ;
		if (ft_zvezda_v_shoke(lisa->tmp_env, myfile->d_name))
		{
			while (myfile->d_name[x])
				lisa->tokens[nomer_ukaza][j++] = myfile->d_name[x++];
			lisa->tokens[nomer_ukaza][j++] = ' ';
			count = 1;
		}
	}
	if (count)
		lisa->tokens[nomer_ukaza][j - 1] = '\0';
	closedir(mydir);
}
