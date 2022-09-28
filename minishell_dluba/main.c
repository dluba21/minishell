#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	
	t_vars	vars;
	t_list **huy; //udalit'
	t_list *head;
	t_list *head_2;
	t_list *head_3;
	t_list	**llst;
	t_list	*llst_elem;
	t_list	**tmp;
	char	*str;
//	char *buffer_1 = ft_strset(100);
//	char *buffer_1;

//    char **pop = big_string_copy(env);
//	big_str_print(env);
	 //while (!exit_f)
//	if (argc == 100)
//		printf("Error");
//	if (!*argv)
//		printf("Error");
	
	if (vars_initializing(&vars, env)) //ОШИБКА - ИНОГДА ФРИШИТСЯ ВТОРОЙ РАЗ!!!!
		return (0);

	
	while (1) //while (!vars->exit_f)
	{
		printf("main proc = %d\n", getpid());
		sig_init();
		str = ft_readline(); //
		if (*str)
		{
			huy = bash_args_lst_lexer(str, &vars);
			llst = llst_new(huy);
			exec_cmd(llst, &vars);
		}
		if (str)
			free(str);
//		break;
//		rl_clear_history();
	}
////	sleep(1000);
//////	free_all;
//
//
////
//
////	huy = bash_args_lst_lexer("ls > $LOGNAME < aboba | a > \"arbidol\" bruh $? | abobus  1 << lol | denis no 3$$$ | pop durak dope ", &vars);
////
////	huy = bash_args_lst_lexer("<< stop cat | cat | ls", &vars);
//
//
////	huy = bash_args_lst_lexer("<< stop cat | << kek cat | cat", &vars);
////	huy = bash_args_lst_lexer("echo aboba | cat", &vars);
//	huy = bash_args_lst_lexer(get_next_line(0), &vars);
//
//
////	char *str = readline("minishell: ");
////	huy = bash_args_lst_lexer("yes | cat | cat", &vars);
//
////	huy = bash_args_lst_lexer(str, &vars);
//
////	huy = bash_args_lst_lexer("< heredoc_file cat | cat | cat", &vars);
////	huy = bash_args_lst_lexer("ls | wc -l", &vars);
////	huy = bash_args_lst_lexer("	ls | cat", &vars);
////	huy = bash_args_lst_lexer("\'ls\'\"aboba\"|cat -l >aboba");
////	huy = bash_args_lst_lexer("12345"); //inf cycle
////	huy = bash_args_lst_lexer("echo \"12345\"\'12345\'cat"); //
////
////	huy = bash_args_lst_lexer("2|cat");
////	huy = bash_args_lst_lexer("ls|cat>aboba");
////		huy = bash_args_first_lst_init(">>");
////	huy = bash_args_first_lst_init("aavabab\"asvasv\"");
//
////	lst_print_tokens(huy);
//	printf("------------begin_list has written--------\n\n\n\n");
//
//
//	llst = llst_new(huy);
////	llst_cmd_print(llst);
//	printf("------------cmd_lst has written--------\n\n\n\n");
//	exec_cmd(llst, &vars);
////	printf("shell_pid = %d", getpid()); //если команда не найдена то почему то два процесса идут, типа после execve надо захватывать статус выхода и дальше ничего не делать
	close(vars.stdin_fd);
	close(vars.stdout_fd);
	printf("\nall is made!!!\n");

}





//echo >>A робит
//echo <<A робит
//<<a>> наполовину робит
//<<||  - ошибка
//aa робит
//"aboba >>" strncmp сегу выдает
//разобраться с " '' "
//дальше писать парсер
//пробелы вообще не нужны ls|cat>aboba
//huy = bash_args_lst_lexer("aboba"); под это не работает парсер на пайпы

//13.06 17:28 переделать parser, чтобы сплитило по пробелам

//"\'ls\'\"aboba\"|cat>aboba" не робит начало


// "echo "aboba"" не робит

//cat "abo<ba" не робит

//ls > ls > ls
//at-f6% << lol << kek
//>> aboba
//	huy = bash_args_lst_lexer("<< | ls << norm azaz | > \"arbidol\" bruh | abobus  1 lol| denis no 3 | pop durak dope"); //redirect posle paypa

//ls >> aboba kek вывод в aboba "kek"


