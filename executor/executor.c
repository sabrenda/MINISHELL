#include "../minishell.h"

void	ft_ampersant(t_monna *lisa, int *count)
{
	lisa->flag_red_files = 0;
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
	lisa->flag_red_files = 0;
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

void	ft_command_start(t_monna *lisa, int *count)      // работа команд
{
	if (!(strcmp(lisa->tokens[*count], "env")))
		lisa->flag_command = ft_env(lisa, count);
	else if (!(strcmp(lisa->tokens[*count], "cd")))
		lisa->flag_command = ft_cd(lisa, count);
	else if (!(strcmp(lisa->tokens[*count], "pwd")))
		lisa->flag_command = ft_pwd(lisa, count);        // если после pwd идут просто аргументы то пропускаешь их до && || | ; или NULL
	else if (!(strcmp(lisa->tokens[*count], "export")))
		lisa->flag_command = ft_export(lisa, count);
	else if (!(strcmp(lisa->tokens[*count], "unset")))
		lisa->flag_command = ft_unset(lisa, count);
	else if (!(strcmp(lisa->tokens[*count], "echo")))
		lisa->flag_command = ft_echo(lisa, count);
	else if (!(strcmp(lisa->tokens[*count], "exit")))
		ft_exit(lisa, count);
}

int	ft_operators_red(char *str)
{
	if ((!(strcmp(str, "&&")) && str[3] == 0)
		|| (!(strcmp(str, "||")) && str[3] == 0)
		|| (!(strcmp(str, "|")) && str[2] == 0)
		|| (!(strcmp(str, ";")) && str[2] == 0))
		return (0);
	return (1);
}

void	ft_redirect_executor(t_monna *lisa, int i)//создает файлы заранее
{
	int fd;

	while (lisa->tokens[i] && ft_operators_red(lisa->tokens[i])) //  echo asd > a > b > c < a
	{
		if ((!(strcmp(lisa->tokens[i], "|")) && lisa->tokens[2] == 0))
			break ;
		if (ft_red_serch(lisa->tokens[i]))
		{
			if (!(strcmp(lisa->tokens[i], ">")) && lisa->tokens[i][2] == 0)
			{
				i++;
				fd = open(lisa->tokens[i], O_WRONLY|O_TRUNC|O_CREAT);
			}
			else if (!(strcmp(lisa->tokens[i], "<")) && lisa->tokens[i][2] == 0)
			{
				i++;
				fd = open(lisa->tokens[i], O_RDONLY);
				if (fd == -1)
				{
					ft_putstr_fd("minishell: ", 1);
					ft_putstr_fd(lisa->tokens[i - 1], 1);
					ft_putendl_fd(" No such file or directory", 1);
					lisa->flag_red_files = 1;
					return ;
				}
			}
			else if (!(strcmp(lisa->tokens[i], ">>")) && lisa->tokens[i][3] == 0)
			{
				i++;
				fd = open(lisa->tokens[i], O_WRONLY|O_CREAT);
			}
			lisa->flag_red_files = 1;
			if (fd > 0)
				close(fd);
		}
		i++;
	}
}

int	ft_executor(t_monna *lisa) // основная функция выполнения
{
	int	count;
	lisa->flag_command = 0; // флаг который определяет выполнилась ли команда (если да то 0, нет 1)
	count = 0;
	while (lisa->tokens[count])
	{
		ft_pipe(lisa, count);
		if (!lisa->flag_red_files)
			ft_redirect_executor(lisa, count);
		if (ft_search_com(lisa->tokens[count])) // ft_search_com смотрит является ли это командой
			ft_command_start(lisa, &count);     // выполнение команд
		else if (!strcmp(lisa->tokens[count], "&&"))
			ft_ampersant(lisa, &count);
		else if (!strcmp(lisa->tokens[count], "||"))
			ft_ili(lisa, &count);
		else if (!strcmp(lisa->tokens[count], ";"))
		{
			lisa->flag_red_files = 0;
			count += 1;
		}
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
 //                    echo asd > a > b
