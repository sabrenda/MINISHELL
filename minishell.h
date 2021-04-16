#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>

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
	int		i;
	int		j;
	int		word;
	int		flag;
	int		count;
	char	c;
}			t_pars;

// typedef struct s_flag
// {
// 	int f_echo;
// 	int f_cd;
// 	int f_pwd;
// 	int f_export;
// 	int f_unset;
// 	int f_env;
// 	int f_exit;
// 	int nothing;
// 	int f_ls;
// 	int f8;
// }				t_flag;

int	parser(char *line, t_monna *lisa);
int	ft_memory_pars(t_monna *lisa, char *line, t_pars *pars);
int	ft_len_words(char *line);
int	ft_len_space_tab(char *line, t_pars *len);
int	ft_lenmassive(char **str);
void	ft_davinci(void);
void	ft_monnalisa(void);
void	ft_monnalisa_2(void);
void	m(char *monna, int lisa);
void	ft_len_kov(t_pars *len, char *line);
void	ft_len_alpha(char *line, t_pars *len);
void	ft_len_kov_pars(t_pars *pars, char *line, t_monna *lisa);
void	ft_len_alpha_pars(char *line, t_pars *pars, t_monna *lisa);

#endif
