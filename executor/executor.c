#include "../minishell.h"

// void ft_ampersant(t_monna *lisa, int *i)
// {
// 	if (flag != 1)
// 	{
// 		while (lisa->tokens[*i] && ft_check(lisa->tokens[*i]))
// 		{
// 			*i++
// 		}

// 	}

// }

// int	ft_echo(t_monna *lisa, int *i)
// {

// int	fd;
// fd = open("fileX", O_CREAT, O_RDWR);

// 	*i++;
// 	while (1)
// 	{
// 		if (lisa->tokens[*i] == NULL || ft_check(lisa->tokens[*i]))
// 		{
// 			file = '\n';
// 			break;
// 		}
// 		if (lisa->tokens[*i] && ft_check(lisa->tokens[*i]) != 1)
// 		{
// 			file = lisa->tokens[*i];
// 			file = ' ';
// 		}
// 		*i++;
// 	}
// 	return (1);
// }

int	ft_operators(char *str) //проверяет является ли это оператором
{
	if ((!(strcmp(str, "&&")) && str[3] == 0)
		|| (!(strcmp(str, "||")) && str[3] == 0)
		|| (!(strcmp(str, "|")) && str[2] == 0)
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
	{
		*count += 1;
	}
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
	// else if (!(strcmp(lisa->tokens[*count], "pwd")))
	// 	lisa->flag_command = ft_pwd(lisa, count);// если после pwd идут просто аргументы то пропускаешь их до && || | ; или NULL
	// else if (!(strcmp(lisa->tokens[*count], "export")))
	// 	lisa->flag_command = ft_export(lisa, count);
	// else if (!(strcmp(lisa->tokens[*count], "unset")))
	// 	lisa->flag_command = ft_unset(lisa, count);
	// else if (!(strcmp(lisa->tokens[*count], "echo")))
	// 	lisa->flag_command = ft_echo(lisa, count); // если после env идут просто аргументы то пропускаешь их до && || | ; или NULL
	// else if (!(strcmp(lisa->tokens[*count], "exit")))
	// 	ft_exit(lisa, count);
}

int	ft_executor(t_monna *lisa) // основная функция выполнения
{
	int	count;

	lisa->flag_command = 0; // флаг который определяет выполнилась ли команда (если да то 0, нет 1)
	count = 0;
	while (lisa->tokens[count])
	{
		if (ft_search_com(lisa->tokens[count])) // ft_search_com смотрит является ли это командой
			ft_command_start(lisa, &count); // выполнение команд
		// else if (strcmp(lisa->tokens[count], "&&") == 0)
		// 	ft_ampersant(lisa, &count); // &&
		// else if (strcmp(lisa->tokens[count], "||") == 0)
		// 	ft_ili(lisa, &count); // ||
		// else if (strcmp(lisa->tokens[count], "|") == 0)
		// 	ft_pipe(lisa); // |
		// else
		// 	ft_prosto_argument(lisa); // blabla
		else
			return (0);
	}
	return (1);
}
