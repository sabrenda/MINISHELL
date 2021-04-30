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
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>

typedef struct s_monna
{
	char	**commands;
	char	**my_env;
	char	**tokens;
	char	*tmp_env;
	int		status;
	// int		pipe;
	char	**pars_tokk;
	int		flag_error;
	int		flag_block_zvezda;
	int		flag_command;
}				t_monna;

typedef struct s_pars
{
	int		i;
	int		j;
	int		word;
	int		flag;
	int		ecran;
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

int	ft_lenmassive(char **str);
int	parser(char *line, t_monna *lisa);
int	ft_operator(t_pars *len, char *line);
int	ft_len_words(char *line, t_monna *lisa);
int	ft_len_space_tab(char *line, t_pars *len);
int	proverka_isdigit(char *line, t_pars *len);
int	ft_zvezda_v_shoke(char *str, char *dir_name);
int	ft_memory_pars(t_monna *lisa, char *line, t_pars *pars);
int	ft_zvezda_nachalo(char *str, char *dir_name, int *flag);
int	ft_zvezda_seredina(char *str, char *dir_name, int *flag);
int	ft_zvezda_konec(char *str, char *dir_name, int *flag);
int	ft_zvezda_nachalo_2(int i, char *str ,char *dir_name);
int ft_zvezda_seredina_2(char *str ,char *dir_name, int *flag);
int ft_zvezda_konec_2(int i, char *str ,char *dir_name);
char	*del_start_space(char *line);
void	ft_davinci(void);
void	ft_monnalisa(void);
void	ft_monnalisa_2(void);
void	m(char *monna, int lisa);
void	ft_len_kov_1(t_pars *n, char *l, t_monna *lisa);
void	ft_len_kov_2(t_pars *len, char *line);
void	ft_len_kov_pars_1(t_pars *pars, char *line, t_monna *lisa);
void	ft_len_kov_pars_2(t_pars *pars, char *line, t_monna *lisa);
void	ft_len_alpha(char *line, t_pars *len, t_monna *lisa);
void	ft_len_alpha_pars(char *line, t_pars *pars, t_monna *lisa);
void	ft_tochka_zapitaya(t_pars *len, char *line);
void	ft_tochka_zapitaya_pars(t_pars *pars, char *line, t_monna *lisa);
void	ft_operator_pars(t_pars *pars, char *line, t_monna *lisa);
void	ft_ecran(char *line, t_pars *len);
void	ft_ecran_pars(t_pars *pars, char *line, t_monna *lisa);
void	ft_redirect_pars(t_pars *len, t_monna *lisa, char *line);
void	ft_redirect(t_pars *len, char *line);
void	ft_dollar_ili_net(t_monna *lisa, t_pars *len);
void	ft_dollar_ili_net_pars(t_monna *lisa, t_pars *pars);
void	ft_kov_dollar(t_monna *lisa, char *line, t_pars *len);
void	ft_kov_dollar_pars(t_monna *lisa, char *line, t_pars *pars);
void	ft_clean_tmp_env(t_monna *lisa);
void	ft_zvezda_epta(t_monna *lisa, int nomer_ukaza);

int	ft_executor(t_monna *lisa);
void	ft_command_start(t_monna *lisa, int *count);
int	ft_search_com(char *str);
int	ft_env(t_monna *lisa, int *count);
void	ft_ili(t_monna *lisa, int *count);
void	ft_ampersant(t_monna *lisa, int *count);
int	ft_operators(char *str);


#endif
