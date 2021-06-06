#include "../minishell.h"

int	ft_bin(char	*str)
{
	DIR *mydir;
	struct dirent *myfile;
	struct stat mystat;

	mydir = opendir("/bin");
	while((myfile = readdir(mydir)) != NULL)
	{
		stat(myfile->d_name, &mystat);
		if (!(strcmp((char *)&myfile->d_name, str)))
			return (1);
	}
	closedir(mydir);
	return (0);
}
void ft_proverka_absol_relat(t_any *any)
{
	any->str = NULL;
	if (ft_bin(any->mas[0])) // bin
		any->str = ft_strjoin("/bin/", any->mas[0]);
	if (!any->str && !(ft_strncmp(any->mas[0], "./", 2))) // релатив
	{
		any->tmp = ft_strjoin(getcwd(NULL, 0) , "/");
		any->str = ft_strjoin(any->tmp , any->mas[0]);
		free (any->tmp);
	}
	if (!any->str) //абсолют
		any->str = ft_strjoin("" , any->mas[0]);
}


int	ft_any_argument(t_monna *lisa, int *count) //
{
	t_any	any;

	any.mas = ft_copy_massive(lisa, *count); //копируем аргументы до "&& || > < ; |"
	ft_proverka_absol_relat(&any); // проверяю /bin/ релативный и абсолютный путь
	any.pid = fork();
	if (any.pid == 0) // Дочерний процесс
	{
		if (execve(any.str, any.mas, lisa->my_env) == -1)
			printf("minishell: %s: command not found\n", any.mas[0]);
		free (any.str);
		exit(EXIT_FAILURE);
	}
	any.wpid = waitpid(any.pid, &any.status, WUNTRACED);
	while (!WIFEXITED(any.status) && !WIFSIGNALED(any.status))
		any.wpid = waitpid(any.pid, &any.status, WUNTRACED);
	any.status = WEXITSTATUS(any.status);
	ft_free_mass(any.mas);
	lisa->flag_bonus_red = 0;
	if (any.status == 256)
		any.status = 127;
	while (lisa->tokens[*count] && ft_operators_2(lisa->tokens[*count]))
		*count += 1;
	return (any.status);
}
