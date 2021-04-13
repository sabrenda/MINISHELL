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
}				t_monna;

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
	i = -1;
	lisa.status = 1;
	while (lisa.status)
	{
		ft_putstr_fd("\033[31m༼ つ ◕_◕ ༽つ\033[32m$ ", 1);
		get_next_line(1, &line); //чтение ввода
		printf("%s\n", line);
		// parser(line, &lisa); //парсим строку
		if (strcmp("exit", line) == 0)
		{
			free(line);
			break;
		}
		free(line);
		// lisa.status = executor(&lisa, env); выполнение
	}
	return (0);
}
