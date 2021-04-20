#include "../minishell.h"

// char *pwd_s = "pwd", ""pwd"", "PWD", ""pwd"";
void ft_env(t_monna lisa, int i)
{
	int c;
	c = 0;
	// char *dif_s;

	if (strcmp(lisa.tokens[0], "env") == 0 && !(lisa.tokens[i + 1]))
	{
		while(lisa.my_env[c])
		{
			// if(strcmp(env[c], lisa.tokens[c]) == 0)
			// {
				// ft_putstr_fd(lisa.tokens[i + 1], 1);
				ft_putstr_fd(lisa.my_env[c], 1);
				write(1, "\n", 1);
				c++;
			// }
			// else
			// {
			// 	diff
			// }
		}
	}
	else
	{	
		if (strcmp(lisa.tokens[1], "pwd") == 0 || strcmp(lisa.tokens[1], "PWD") == 0)
		{
			ft_putstr_fd(getcwd(NULL, 1), 1);
			write(1, "\n", 1);
		}
		else
		{
			ft_putstr_fd("env: ", 1);
			ft_putstr_fd(lisa.tokens[1], 1);
			ft_putstr_fd(": No such file or directory\n", 1);
		}
	}
}



// void ft_env(t_monna lisa, int i)
// {
// 	int c;
// 	c = 0;
// 	char *dif_s;

// 	if (strcmp(lisa.tokens[i], "env") == 0 && !(lisa.tokens[i+1]))
// 	{
// 		while(lisa.my_env[c])
// 		{
// 			if(strcmp(env[c], lisa.tokens[c]) == 0)
// 			{
// 				ft_putstr_fd(lisa.my_env[c], 1);
// 				write(1, "\n", 1);
// 				c++;
// 			}
// 			// else
// 			// {
// 			// 	diff
// 			// }
// 		}
// 	}
// 	if (strcmp(lisa.tokens[i], "pwd") == 0 || strcmp(lisa.tokens[i], "PWD") == 0)
// 	{	
// 		if (strcmp(lisa.tokens[i], "pwd") == 0 || strcmp(lisa.tokens[i], "PWD") == 0)
// 		{
// 			ft_putstr_fd(getcwd(NULL, 1), 1);
// 			write(1, "\n", 1);
// 		}
// 		else
// 		{
// 			ft_putstr_fd("env: ", 1);
// 			ft_putstr_fd(lisa.tokens[1], 1);
// 			ft_putstr_fd(": No such file or directory\n", 1);
// 		}
// 	}
// }
