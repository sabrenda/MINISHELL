#include "../minishell.h"

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

void	ft_ampersant(t_monna *lisa, int *count)
{
	if (lisa->flag_command == 1) //если в прошлой отработке была ошибка то пропускаем аргументы до оператора || или ;
	{
		while (lisa->tokens[*count] && strcmp(lisa->tokens[*count], "||")
			&& strcmp(lisa->tokens[*count], ";")) // пример: sdfsdfsd && -> пропуск (echo lala asdds sdds) || echo lala
			*count += 1;
	}
	else
		*count += 1;
}

void	ft_ili(t_monna *lisa, int *count)
{
	if (lisa->flag_command == 0) //если в прошлой отработке не было ошибки то пропускаем аргументы до оператора | && и ;
	{
		while (lisa->tokens[*count] && strcmp(lisa->tokens[*count], "|")
			&& strcmp(lisa->tokens[*count], "&&")
				&& strcmp(lisa->tokens[*count], ";")) // пример: echo kola || -> пропуск (echo lala asdds sdds) || echo lala
			*count += 1;
	}
	else
	{
		*count += 1;
	}
}

int	ft_search_com(char *str) // является ли это комадой
{
	if (!(strcmp(str, "echo")) || !(strcmp(str, "cd")) || !(strcmp(str, "pwd"))
		|| !(strcmp(str, "export")) || !(strcmp(str, "unset"))
			|| !(strcmp(str, "env")) || !(strcmp(str, "exit")))
		return (1);
	return (0);
}

void	ft_command_start(t_monna *lisa, int *count) // работа команд
{
	if (!(strcmp(lisa->tokens[*count], "env")))
		lisa->flag_command = ft_env(lisa, count);
	// else if (!(strcmp(lisa->tokens[*count], "cd")))
	// 	lisa->flag_command = ft_cd(lisa, count);
	else if (!(strcmp(lisa->tokens[*count], "pwd")))
		lisa->flag_command = ft_pwd(lisa, count);// если после pwd идут просто аргументы то пропускаешь их до && || | ; или NULL
	// else if (!(strcmp(lisa->tokens[*count], "export")))
	// 	lisa->flag_command = ft_export(lisa, count);
	// else if (!(strcmp(lisa->tokens[*count], "unset")))
	// 	lisa->flag_command = ft_unset(lisa, count);
	// else if (!(strcmp(lisa->tokens[*count], "echo")))
	// 	lisa->flag_command = ft_echo(lisa, count); // если после env идут просто аргументы то пропускаешь их до && || | ; или NULL
	// else if (!(strcmp(lisa->tokens[*count], "exit")))
	// 	ft_exit(lisa, count);
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
	str = (char **)malloc(sizeof(char *) * (j + 1));
	j = 0;
	while (lisa->tokens[i] && ft_operators(lisa->tokens[i]))
	{
		str[j] = ft_strdup(lisa->tokens[i]);
		j++;
		i++;
	}
	str[j] = NULL;
	return (str);
}
void	ft_free_mass(char	**mas)
{
	int	i = 0;

	while (mas[i])
		free (mas[i++]);
	free (mas);
}

int	ft_any_argument(t_monna *lisa, int *count)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char	*str;
	char	**mas;

	mas = ft_copy_massive(lisa, *count);
	pid = fork();
	if (pid == 0) // Дочерний процесс
	{
		str = ft_strjoin("/bin/", mas[0]);
		if (execve(str, mas, lisa->my_env) == -1)
		{
			printf("minishell: %s: command not found\n", mas[0]);
			lisa->flag_error = 1;
		}
		free (str);
		exit(EXIT_FAILURE);
	}
	else // Родительский процес
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	ft_free_mass(mas);
	mas = NULL;
	return (status);
}

int	ft_executor(t_monna *lisa) // основная функция выполнения
{
	int	count;
	// int fildes[2];
	// 0 - 0
	// int std1 = dup(1);
	// dup2(fildes[1], 1);
	// dup2(fildes[0], 0);
	// 1 - 1
	lisa->flag_command = 0; // флаг который определяет выполнилась ли команда (если да то 0, нет 1)
	count = 0;
	while (lisa->tokens[count])
	{
		if (ft_search_com(lisa->tokens[count])) // ft_search_com смотрит является ли это командой
			ft_command_start(lisa, &count); // выполнение команд
		else if (strcmp(lisa->tokens[count], "&&") == 0)
			ft_ampersant(lisa, &count); // &&
		else if (strcmp(lisa->tokens[count], "||") == 0)
			ft_ili(lisa, &count); // ||
		// else if (strcmp(lisa->tokens[count], "|") == 0)
		// 	ft_pipe(lisa); // |
		else
		{
			lisa->flag_command = ft_any_argument(lisa, &count); // blabla
			lisa->flag_error = lisa->flag_command;
			while (lisa->tokens[count] && ft_operators(lisa->tokens[count])) //пропускаем аргрументы если есть после env, так как по сабжу без них надо
				count += 1;
		}
		if (lisa->tokens[count] == NULL)
			return (0);
	}
	// dup2(std1, 1);
	return (1);
}
