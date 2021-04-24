// bash: pwdm: command not found  
void write1_err(char *word)
{
    ft_putstr_fd("Monolisa: ", 1);
    ft_putstr_fd(word, 1);
    ft_putendl_fd(": command not found", 1);
}

//bash: cd: wlpe: No such file or directory  
//cd //ls //cat //env
void write2_err(char *word, char *cmd)
{
    ft_putstr_fd("Monolisa: ", 1);
    ft_putstr_fd(cmd, 1);
    ft_putstr_fd(": ", 1);
    ft_putstr_fd(word, 1);
    ft_putendl_fd(": No such file or directory", 1);

}

//bash: export: `12': not a valid identifier 
//export //unset
void write3_err(char *word, char *cmd)
{
    ft_putstr_fd("Monolisa: ", 1);
    ft_putstr_fd(cmd, 1);
    ft_putstr_fd(": `", 1);
    ft_putstr_fd(word, 1);
    ft_putendl_fd("': not a valid identifier", 1);

}

// open 
// The file /Users/out-shekhovtsova2-vv/mylis/4 does not exist.
void write4_err(char *word)
{
    // str = pwd // /Users/out-shekhovtsova2-vv/mylis/4
      // pwd = getcwd(NULL, 0);
    ft_putstr_fd("The file ", 1);
    ft_putstr_fd(getcwd(NULL, 0), 1);
    ft_putstr_fd("/", 1);
    ft_putstr_fd(word, 1);
    ft_putendl_fd(" does not exist.", 1);
}

// не знаю нужно ли такое, но нашла
// Ввожу : echo $(($1 + $2))
// bash: + : syntax error: operand expected (error token is " ")

// bash-3.2$ echo $(($1  - 23w+- $2))
// bash: - 23w: value too great for base (error token is "23w")

// void write5_err(char *word)
// {
//     ft_putstr_fd("Monolisa: ", 1);
//     ft_putstr_fd(, 1); ???
//     ft_putstr_fd(" : syn", 1);
//     ft_putstr_fd(word, 1);
//     ft_putendl_fd("': not a valid identifier", 1);

// }