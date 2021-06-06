#include "../minishell.h"

void	ft_ampersant(t_monna *lisa, int *count)
{
	lisa->flag_red_files = 0;
	if (lisa->flag_command) //если в прошлой отработке была ошибка то пропускаем аргументы до оператора || или ;
	{
		while (lisa->tokens[*count] && ft_strcmp(lisa->tokens[*count], "||")
			&& ft_strcmp(lisa->tokens[*count], ";")) // пример: sdfsdfsd && -> пропуск (echo lala asdds sdds) || echo lala
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
		while (lisa->tokens[*count] && ft_strcmp(lisa->tokens[*count], "|")
			&& ft_strcmp(lisa->tokens[*count], "&&")
				&& ft_strcmp(lisa->tokens[*count], ";")) // пример: echo kola || -> пропуск (echo lala asdds sdds) || echo lala
			*count += 1;
	}
	else
	{
		*count += 1;
	}
}

void	ft_command_start(t_monna *lisa, int *count)      // работа команд
{
	if (!(ft_strcmp(lisa->tokens[*count], "env")))
		lisa->flag_command = ft_env(lisa, count);
	else if (!(ft_strcmp(lisa->tokens[*count], "cd")))
		lisa->flag_command = ft_cd(lisa, count);
	else if (!(ft_strcmp(lisa->tokens[*count], "pwd")))
		lisa->flag_command = ft_pwd(lisa, count);        // если после pwd идут просто аргументы то пропускаешь их до && || | ; или NULL
	else if (!(ft_strcmp(lisa->tokens[*count], "export")))
		lisa->flag_command = ft_export(lisa, count);
	else if (!(ft_strcmp(lisa->tokens[*count], "unset")))
		lisa->flag_command = ft_unset(lisa, count);
	else if (!(ft_strcmp(lisa->tokens[*count], "echo")))
		lisa->flag_command = ft_echo(lisa, count);
	else if (!(ft_strcmp(lisa->tokens[*count], "exit")))
		ft_exit(lisa, count);
}

int	ft_operators_red(char *str)
{
	if ((!(ft_strcmp(str, "&&")) && str[3] == 0)
		|| (!(ft_strcmp(str, "||")) && str[3] == 0)
		|| (!(ft_strcmp(str, "|")) && str[2] == 0)
		|| (!(ft_strcmp(str, ";")) && str[2] == 0))
		return (0);
	return (1);
}

void	ft_redirect_end(t_monna *lisa)
{
	if (lisa->flag_red_input)
	{
		dup2(lisa->fd_input, 0);
	}
	if (lisa->flag_red_output)
	{
		dup2(lisa->fd_output, 1);
	}
}

void	ft_redirect_executor(t_monna *lisa, int i, int *count)//создает файлы заранее
{
	int fd;

	while (lisa->tokens[i] && ft_operators_red(lisa->tokens[i])) //  echo asd > a > b > c < a
	{
		if ((!(ft_strcmp(lisa->tokens[i], "|")) && lisa->tokens[2] == 0))
			break ;
		if (ft_red_serch(lisa->tokens[i]))
		{
			if (!(ft_strcmp(lisa->tokens[i], ">")) && lisa->tokens[i][2] == 0)
			{
				i++;
				fd = open(lisa->tokens[i], O_WRONLY|O_TRUNC|O_CREAT, S_IWRITE | S_IREAD);
			}
			else if (!(ft_strcmp(lisa->tokens[i], "<")) && lisa->tokens[i][2] == 0)
			{
				i++;
				fd = open(lisa->tokens[i], O_RDONLY);
				if (fd == -1)
				{
					ft_putstr_fd("minishell: ", 1);
					ft_putstr_fd(lisa->tokens[i - 1], 1);
					ft_putendl_fd(" No such file or directory", 1);
					lisa->flag_red_files = 1;
					lisa->flag_command = 1;
					lisa->flag_error = 1;
					while(lisa->tokens[*count] && search_arg_2(lisa, count))
						*count += 1;
					return ;
				}
			}
			else if (!(ft_strcmp(lisa->tokens[i], ">>")) && lisa->tokens[i][3] == 0)
			{
				i++;
				fd = open(lisa->tokens[i], O_WRONLY|O_CREAT, S_IWRITE | S_IREAD);
			}
			lisa->flag_red_files = 1;
			if (fd > 0)
				close(fd);
			if (fd == -1)
				return ;
		}
		i++;
	}
}

void	ft_incepcion_red(t_monna *lisa, char *str)
{
	int	i;

	lisa->flag_bonus_red = 1;
	lisa->bonus_red = (char **)malloc(sizeof(char *) * 2);
	lisa->bonus_red[0] = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	lisa->bonus_red[1] = NULL;
	i = 0;
	while (i < ft_strlen(str))
	{
		lisa->bonus_red[0][i] = str[i];
		i++;
	}
	lisa->bonus_red[0][i] = '\0';
}

void	ft_continue_red(t_monna *lisa, char *new_word)
{
	int		i;
	int		j;
	int		len;
	char	**str;

	len = ft_lenmassive(lisa->bonus_red);
	str = (char **)malloc(sizeof(char *) * (len + 2));
	str[len + 1] = NULL;
	i = 0;
	while(i < len)
	{
		str[i] = (char *)malloc(sizeof(char) * (ft_strlen(lisa->bonus_red[i]) + 1));
		j = 0;
		while(j < ft_strlen(lisa->bonus_red[i]))
		{
			str[i][j] = lisa->bonus_red[i][j];
			j++;
		}
		str[i][j] = '\0';
		i++;
	}
	j = 0;
	while(new_word[j])
	{
		str[i][j] = new_word[j];
		j++;
	}
	str[i][j] = '\0';
	ft_free_mass(lisa->bonus_red);
	lisa->bonus_red = str;
}

void	ft_red_1(t_monna *lisa, int *count)
{
	int	fd;

	lisa->flag_red_output = 1;
	*count += 1;
	fd = open(lisa->tokens[*count], O_WRONLY|O_TRUNC|O_CREAT, S_IWRITE | S_IREAD);
	dup2(fd,1);
	close(fd);
}

void	ft_red_2(t_monna *lisa, int *count)
{
	int	fd;

	lisa->flag_red_input = 1;
	*count += 1;
	fd = open(lisa->tokens[*count], O_RDONLY);
	dup2(fd, 0);
	close(fd);
}

void	ft_red_3(t_monna *lisa, int *count)
{
	int	fd;

	lisa->flag_red_output = 1;
	*count += 1;
	fd = open(lisa->tokens[*count], O_WRONLY|O_CREAT, S_IWRITE | S_IREAD);
	dup2(fd,1);
	close(fd);
}

void	ft_red_4(t_monna *lisa, int *count) // добить ----------------
{
	int		temp_fd_out;
	int		temp_fd_in;
	char	*str;

	lisa->flag_red_input = 1;
	lisa->flag_red_output = 1;
	dup2(1, temp_fd_out);
	dup2(lisa->fd_output, 1);
	dup2(0, temp_fd_in);
	dup2(lisa->fd_input, 0);
	*count += 1;
	while(1)
	{
		ft_putstr_fd("> ", 1);
		get_next_line(0, &str);
		if (!ft_strcmp(str, lisa->tokens[*count]))
		{
			if (str)
				free (str);
			break ;
		}
		if (!lisa->bonus_red)
			ft_incepcion_red(lisa, str); // добить // создание 2-го массива
		else
			ft_continue_red(lisa, str); // добить // продолжение строк , потом сделать в any_arg и в других чтение из fd 0 с функции ft_putendl_fd
		if (str)
			free (str);
	}
	int i = 0;
	if (lisa->flag_bonus_red)//malloc
	{
		while(i < ft_lenmassive(lisa->bonus_red))
		{
			ft_putendl_fd(lisa->bonus_red[i], 0);
			i++;
		}
	}
	if (lisa->bonus_red)
		ft_free_mass(lisa->bonus_red);
	lisa->bonus_red = NULL;
	dup2(temp_fd_out, 1);
	dup2(temp_fd_in, 0);
	close(temp_fd_out);
	close(temp_fd_in);
}

void	ft_redirect_executor_2(t_monna *lisa, int i, int *count) // осталось добить функции ft_red и сделать как ft_pipe2 для возвразения фд дескрипторов 1 и 0 на полку как было
{
	while (lisa->tokens[i] && ft_operators(lisa->tokens[i]))
		i++;
	if (lisa->tokens[i] && ft_red_serch(lisa->tokens[i]))
	{
		while (lisa->tokens[i] && !ft_red_serch_2(lisa->tokens[i]))
		{
		if (!(ft_strcmp(lisa->tokens[i], ">")) && lisa->tokens[i][2] == 0)
			ft_red_1(lisa, &i);
		else if (!(ft_strcmp(lisa->tokens[i], "<")) && lisa->tokens[i][2] == 0)
			ft_red_2(lisa, &i);
		else if (!(ft_strcmp(lisa->tokens[i], ">>")) && lisa->tokens[i][3] == 0)
			ft_red_3(lisa, &i);
		else if (!(ft_strcmp(lisa->tokens[i], "<<")) && lisa->tokens[i][3] == 0)
			ft_red_4(lisa, &i);
		else
			i++;
		}
	}
}

void	ft_executor(t_monna *lisa) // основная функция выполнения
{
	int	count;

	lisa->flag_command = 0; // флаг который определяет выполнилась ли команда (если да то 0, нет 1)
	count = 0;
	while (lisa->tokens[count])
	{
		ft_pipe(lisa, count);
		if (!lisa->flag_red_files)
			ft_redirect_executor(lisa, count, &count);
		ft_redirect_executor_2(lisa, count, &count);
		if (ft_search_com(lisa->tokens[count])) // ft_search_com смотрит является ли это командой
			ft_command_start(lisa, &count);     // выполнение команд
		else if (!ft_strcmp(lisa->tokens[count], "&&"))
			ft_ampersant(lisa, &count);
		else if (!ft_strcmp(lisa->tokens[count], "||"))
			ft_ili(lisa, &count);
		else if (!ft_strcmp(lisa->tokens[count], ";"))
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
		ft_redirect_end(lisa);
	}
}
 //                    echo asd jjn jnjn jj > a >> b
