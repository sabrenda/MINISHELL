#include "minishell.h"

char *ft_pwd(char *str)
{
    char *s1;

    s1 = getcwd(NULL, 0);
    strlcat(s1, "\n", ft_strlen(s1) + 2);
    return (s1);
}

void ft_echo(char **str)
{
    int i = 1;
    int fl_cmd = 0;

    if(strcmp("-n", str[1]) == 0)
        ft_putstr_fd(NULL, 1);
    else if(*str[1] == '$')
    {
        // ft_putstr_fd("$-tut", 1);
        // printf("s:%s\n", *str);
        // printf("s1:%s\n", str[i++]);
        // printf("c:%c\n", *str[i]);
        fl_cmd = 1;
        if(strcmp("$PWD", str[i++]) == 0)
        {
            ft_putstr_fd(getcwd(NULL, 0), 1);
            ft_putstr_fd("\n", 1);
        }
    }
    else
    {
        ft_putstr_fd(str[1], 1);
        ft_putstr_fd("\n", 1);
    }
}

int main(void)
{
    char *ar[2];

    ar[0] = "echo";
    // ar[1] =  "echo";

    ft_echo(ar);
}
