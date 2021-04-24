// команда или слово / 0 - команда / 1 - слово
void cmd_or_word(char **my_env)
{
    if (strcmp(my_env[1], "echo") == 0 ||
    strcmp(my_env[1], "cd") == 0 ||
    strcmp(my_env[1], "pwd") == 0 ||
    strcmp(my_env[1], "export") == 0 ||
    strcmp(my_env[1], "unset") == 0 ||
    strcmp(my_env[1], "env") == 0 ||
    strcmp(my_env[1], "exit") == 0)
        return (0)
    else
        return (1);
}


// какая команда // флаги ? записть в структуру ?
// void search_cmd(t_flag *fl, char *str)
//{
//	if (strcmp(str, "echo") == 0)
//		fl->f_echo = 1;
//	else if (strcmp(str, "cd") == 0)
//		fl->f_cd = 1;
//	else if (strcmp(str, "pwd") == 0)
//		fl->f_pwd = 1;
//	else if (strcmp(str, "export") == 0)
//		fl->f_export = 1;
//	else if (strcmp(str, "unset") == 0)
//		fl->f_unset = 1;
//	else if (strcmp(str, "env") == 0)
//		fl->f_env = 1;
//	else if (strcmp(str, "ls") == 0)
//		fl->f_exit = 1;
//	else if (strcmp(str, "exit") == 0)
//		fl->f_exit = 1;
//	else
//		fl->nothing = 1;
//}