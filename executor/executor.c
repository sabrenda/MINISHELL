#include "../minishell.h"

void	ft_ampersant(t_monna *lisa, int *count)
{
	if (lisa->flag_command) //если в прошлой отработке была ошибка то пропускаем аргументы до оператора || или ;
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
	if (!lisa->flag_command) //если в прошлой отработке не было ошибки то пропускаем аргументы до оператора | && и ;
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

void	ft_command_start(t_monna *lisa, int *count) // работа команд
{
	if (!(strcmp(lisa->tokens[*count], "env")))
		lisa->flag_command = ft_env(lisa, count);
	else if (!(strcmp(lisa->tokens[*count], "cd")))
		lisa->flag_command = ft_cd(lisa, count);
	else if (!(strcmp(lisa->tokens[*count], "pwd")))
		lisa->flag_command = ft_pwd(lisa, count);// если после pwd идут просто аргументы то пропускаешь их до && || | ; или NULL
	else if (!(strcmp(lisa->tokens[*count], "export")))
		lisa->flag_command = ft_export(lisa, count);
	else if (!(strcmp(lisa->tokens[*count], "unset")))
		lisa->flag_command = ft_unset(lisa, count);
	else if (!(strcmp(lisa->tokens[*count], "echo")))
		lisa->flag_command = ft_echo(lisa, count);
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
		ft_pipe(lisa, count);
		if (ft_search_com(lisa->tokens[count])) // ft_search_com смотрит является ли это командой
			ft_command_start(lisa, &count); // выполнение команд
		else if (!strcmp(lisa->tokens[count], "&&"))
			ft_ampersant(lisa, &count);
		else if (!strcmp(lisa->tokens[count], "||"))
			ft_ili(lisa, &count);
		else
		{
			lisa->flag_command = ft_any_argument(lisa, &count); // другая команда либо ошибка
			lisa->flag_error = lisa->flag_command;
		}
		ft_pipe2(lisa, &count);
		if (lisa->tokens[count] == NULL)
			return (0);
	}
	return (1);
}
