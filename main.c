#include <string.h>
#include "libft/libft.h"
#include "libft/get_next_line.h"

void	m(char *monna, int lisa);

typedef struct s_monna
{
	char	**commands;
	char	**my_env;
	char	**tokens;
	int		status;
	int		pipe;
}				t_monna;

typedef struct s_pars
{
	int	i;
	int j;
	int	word;
	int flag;
	char c;
}				t_pars;

void	m(char *monna, int lisa)
{
	write(lisa, monna, ft_strlen(monna));
}


void	ft_monnalisa(void)
{
	m("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>''''''<!!!!!!!!!!!!!!!!!!!!!!!\n", 1);
	m("!!!!!!!!!!!!!!!!!!!!!!!!'''''`             ``'!!!!!!!!!!!!!!!!!!!\n", 1);
	m("!!!!!!!!!!!!!!!!!!!!''`          .....         `'!!!!!!!!!!!!!!!!\n", 1);
	m("!!!!!!!!!!!!!!!!!'`      .      :::::'            `'!!!!!!!!!!!!!\n", 1);
	m("!!!!!!!!!!!!!!!'     .   '     .::::'                `!!!!!!!!!!!\n", 1);
	m("!!!!!!!!!!!!!'      :          `````                   `!!!!!!!!!\n", 1);
	m("!!!!!!!!!!!!        .,cchcccccc,,.                       `!!!!!!!\n", 1);
	m("!!!!!!!!!!!     .-c?$$$$$$$$$$$$$$c,                      `!!!!!!\n", 1);
	m("!!!!!!!!!!    ,ccc$$$$$$$$$$$$$$$$$$$,                     `!!!!!\n", 1);
	m("!!!!!!!!!    z$$$$$$$$$$$$$$$$$$$$$$$$;.                    `!!!!\n", 1);
	m("!!!!!!!!    <$$$$$$$$$$$$$$$$$$$$$$$$$$:.                    `!!!\n", 1);
	m("!!!!!!!     $$$$$$$$$$$$$$$$$$$$$$$$$$$h;:.                   !!!\n", 1);
	m("!!!!!!'     $$$$$$$$$$$$$$$$$$$$$$$$$$$$$h;.                   !!\n", 1);
	m("!!!!!'     <$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$                   !!\n", 1);
	m("!!!!'      `$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$F                   `!\n", 1);
	m("!!!!        c$$$$&&&$$$$$$$P##  ccc&&&&&&c                      !\n", 1);
	m("!!!         `cc .,.. c$$$$F    .,zcr                           !!\n", 1);
	m("!!!         .  dL    .?$$$   .,cc,      .,z$h.                 !!\n", 1);
	m("!!!!        <. $$c= <$d$$$   <$$$$=-=+c$$$$$$$                 !!\n", 1);
	m("!!!         d$$$hcccd$$$$$   d$$$hcccd$$$$$$$F                 !!\n", 1);
	m("!!         ,$$$$$$$$$$$$$$h d$$$$$$$$$$$$$$$$                 !!!\n", 1);
	m("!          `$$$$$$$$$$$$$$$<$$$$$$$$$$$$$$$$'                !!!!\n", 1);
	m("!          `$$$$$$$$$$$$$$$$c$$$$$$$$$$$$$P>                !!!!!\n", 1);
}

void	ft_monnalisa_2(void)
{
	m("!           ?$$$$$$$$$$$$??$c`$$$$$$$$$$$?>'                `!!!!\n", 1);
	m("!           `?$$$$$$I7?&&    ,$$$$$$$$$?>>'                  !!!!\n", 1);
	m("!.           <<?$$$$$$c.    ,d$$?$$$$$F>>''                  `!!!\n", 1);
	m("!!            <i?$Pc??$$r--c?cc  ,$$$$h;>''                  `!!!\n", 1);
	m("!!             $$$hccccccccc= cc$$$$$$$>>'                    !!!\n", 1);
	m("!              `?$$$$$$Fcccc  `c$$$$$>>>''                    `!!\n", 1);
	m("!                c?$$$$$cccccc$$$$cc>>>>'                      !!\n", 1);
	m("!                  c$$$$$$$$$$$$$F>>>>''                      `!!\n", 1);
	m("!                    c$$$$$$$$ccc>'''                           !\n", 1);
	m("!>                     `ccccccc                                 !\n", 1);
	m("!!;                       .                                     !\n", 1);
	m("!!!                       ?h.                                   !\n", 1);
	m("!!!!                       $$c,                                 !\n", 1);
	m("!!!!>                      ?$$$h.              .,c             !!\n", 1);
	m("!!!!!                       $$$$$$$$$hc,.,,cc$$$$$             !!\n", 1);
	m("!!!!!                  .,zcc$$$$$$$$$$$$$$$$$$$$$$             !!\n", 1);
	m("!!!!!               .z$$$$$$$$$$$$$$$$$$$$$$$$$$$$             !!\n", 1);
	m("!!!!!             ,d$$$$\033[35m|..@Tchariss..|\033[0m$$$$$$$$$    \n", 1);
	m("!!!!!           ,d$$$$$$\033[36m|..@Sabrenda..|\033[0m$$$$$$$$   \n", 1);
	m("!!!!!         ,d$$$$$$$$\033[31m|..MonnaLisa..|\033[0m$$$$$$$  \n", 1);
	m("!!!!>        c$$$$$$$$$$\033[32m|..MiniShell..|\033[0m$$$$$  \n", 1);
}

void	ft_davinci(void)
{
	ft_monnalisa();
	ft_monnalisa_2();
}

int	ft_lenmassive(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_len(char *line)
{
	t_pars	len;

	int count = 0;
	ft_bzero(&len, sizeof(t_pars));
	while (line[len.i])
	{
		if (line[len.i] == '\t' || line[len.i] == ' ')
		{
			while (line[len.i] == '\t' || line[len.i] == ' ')
				len.i++;
			if (line[len.i] == '\0')
				break ;
		}
		if (line[len.i] == '\"' || line[len.i] == '\'')
		{
			len.c = line[len.i];
			while (1) // СДЕЛАТЬ ОТДЕЛЬНУЮ ФУНКЦИЮ КОТОРАЯ ПРОВЕРЯЕТ НА НАЛИЧИЕ НОРМ СИМВОЛОВ
			{
				len.i++;
				count++;
				if (line[len.i] == '\0')
				{
					line[len.i++] = len.c;
					line[len.i] = '\0';
					// if (count == 1)
					// 	len.flag = 1;
					break ;
				}
				if (line[len.i] == len.c)
				{
					len.i++;
					// if (count == 1)
					// 	len.flag = 1;
					break ;
				}
			}
		}
		while(line[len.i] != ' ' && line[len.i] != '\t' && line[len.i] && line[len.i] != '\"' && line[len.i] != '\'')
			len.i++;
		len.word++;
		if (line[len.i] == '\0')
			break;
	}
	return (len.word);
}

int ft_memory_pars(t_monna *lisa, char *line, t_pars	*pars)
{
	int	i;

	i = 0;
	lisa->tokens = (char **)malloc(sizeof(char *) * (ft_len(line) + 1));
	if (lisa->tokens == NULL)
		return (0);
	lisa->tokens[ft_len(line)] = NULL;
	while (i < ft_len(line))
	{
		lisa->tokens[i] = (char *)malloc(sizeof(char) * 1000);
		if (lisa->tokens[i] == NULL)
			return (0);
		i++;
	}
	if (ft_len(line) == 0)
		lisa->tokens[i] = NULL;
	pars->i = 0;
	pars->word = -1;
	return (1);
}

int	parser(char *line, t_monna *lisa)
{
	t_pars	pars;

	if (ft_memory_pars(lisa, line, &pars) == 0)
		return (0);
	while (++pars.word < ft_len(line) && line[pars.i])
	{
		pars.j = 0;
		pars.flag = 1;
		while (line[pars.i] && pars.flag)
		{
			if (line[pars.i] == '\t' || line[pars.i] == ' ')
				while (line[pars.i] == '\t' || line[pars.i] == ' ')
					pars.i++;
			if (line[pars.i] == '\0')
				break;
			while (line[pars.i] != '\t' && line[pars.i] != ' ' && line[pars.i] != '\0')
			{
				if (line[pars.i] == '\"' || line[pars.i] == '\'')
				{
					pars.c = line[pars.i++];
					while (line[pars.i])
					{
						if (pars.c == line[pars.i])
						{
							pars.i++;
							if (line[pars.i] == '\0')
							{
								lisa->tokens[pars.word][pars.j] = line[pars.i];
								return (1);
							}
							continue ;
						}
						lisa->tokens[pars.word][pars.j++] = line[pars.i++];
					}
				}
				lisa->tokens[pars.word][pars.j++] = line[pars.i++];
			}
			pars.flag = 0;
		}
		lisa->tokens[pars.word][pars.j] = '\0';
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	int		status;
	int		i;
	t_monna	lisa;

	ft_davinci();
	lisa.my_env = (char **)malloc(sizeof(char *) * ft_lenmassive(env) + 1);
	lisa.my_env[ft_lenmassive(env)] = NULL;
	i = -1;
	while (env[++i])
		lisa.my_env[i] = ft_strdup(env[i]);
	lisa.status = 1;
	while (lisa.status)
	{
		ft_putstr_fd("\033[31m༼ つ ◕_◕ ༽つ\033[32m$ ", 1);
		get_next_line(0, &line); //чтение ввода
		// printf("%s\n", line);
		printf("words = %d\n", ft_len(line));
		parser(line, &lisa); //парсим строку
		i = 0;
		while (lisa.tokens[i])
		{
			ft_putstr_fd(lisa.tokens[i], 1);
			write(1, "\n", 1);
			i++;
		}
		if (strcmp("exit", line) == 0)
		{
			free(line);
			break;
		}
		free(line);
		// lisa.status = executor(&lisa, env); выполнение
	}
	return (1);
}
