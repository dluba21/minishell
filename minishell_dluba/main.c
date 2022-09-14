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
	char *str;
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
	
//	while (1) //while (!vars->exit_f)
//	{
//		str = ft_readline(); //
//		huy = bash_args_lst_lexer(str, &vars);
//		llst = llst_new(huy);
//		exec_cmd(llst, &vars);
//		if (str)
//			free(str);
////		rl_clear_history();
//	}
////	free_all;
	
	
	
	
	
//	big_str_print(env);
//	root_paths_init(&vars);



//	char *key;
//	buffer_1 = env_trimmer(vars.envp[0], buffer_1);
//	printf("str = {%s}", buffer_1);
//	int i = 0;
//	while (*vars.envp)
//	{
//		printf("[%d]\n", i);
//		env_var_trimmer(vars.envp[0], &buffer_1);
//		printf("str = [%s]\n", *vars.envp);
//		printf("buffer = [%s]\n", buffer_1);
//		key = env_key_trimmer(*vars.envp);
//		printf("key = [%s]\n", key);
//		printf("\n\n");
//		vars.envp++;
//		i++;
//	}
//	printf("len_env = %d\n", i);

//	TERM_PROGRAM=Apple_Terminal
//	printf("d = %d\n", ft_strlen(buffer_1));
//	printf("pointer = [%p]\n", buffer_1);
//	printf("*pointer = [%p]\n", &buffer_1);
//	buffer = ft_strset(100);
//	big_str_print(vars.envp);

//	dollar_expansion(ft_strdup("aboba$LOGNAME $pop $zhopa govno\n"), &vars); //убивает пробел между переменными куда-то
//	dollar_expansion(ft_strdup("aboba$12354aas$? \n"), &vars); //убивает пробел между переменными куда-то
//	dollar_expansion(ft_strdup("ls > $? < aboba | > \"arbidol\" bruh | abobus  1 lol| denis no 3 | pop durak dope"), &vars);
//	while (!vars->exit_f)
//	{
//	}
//	printf("len = %d\n", big_str_len(env));
//	huy = bash_args_lst_lexer("<< kek << ls << norm azaz | > \"arbidol\" bruh | abobus  1 lol| denis no 3 | pop durak dope", &vars);
	//___________________________________________________________________________________________________________________________
//	huy = bash_args_lst_lexer("ls > $LOGNAME < aboba | a > \"arbidol\" bruh $? | abobus  1 << lol | denis no 3$$$ | pop durak dope ", &vars);
//
//	huy = bash_args_lst_lexer("<< stop cat | cat | ls", &vars);


	huy = bash_args_lst_lexer(get_next_line(0), &vars);
//	char *str = readline("minishell: ");
//	huy = bash_args_lst_lexer("yes | cat | cat", &vars);

//	huy = bash_args_lst_lexer(str, &vars);

//	huy = bash_args_lst_lexer("< heredoc_file cat | cat | cat", &vars);
//	huy = bash_args_lst_lexer("ls | wc -l", &vars);
//	huy = bash_args_lst_lexer("	ls | cat", &vars);
//	huy = bash_args_lst_lexer("\'ls\'\"aboba\"|cat -l >aboba");
//	huy = bash_args_lst_lexer("12345"); //inf cycle
//	huy = bash_args_lst_lexer("echo \"12345\"\'12345\'cat"); //
//
//	huy = bash_args_lst_lexer("2|cat");
//	huy = bash_args_lst_lexer("ls|cat>aboba");
//		huy = bash_args_first_lst_init(">>");
//	huy = bash_args_first_lst_init("aavabab\"asvasv\"");

//	lst_print_tokens(huy);
	printf("------------begin_list has written--------\n\n\n\n");


	llst = llst_new(huy);
//	llst_cmd_print(llst);
	printf("------------cmd_lst has written--------\n\n\n\n");
	exec_cmd(llst, &vars);
//	printf("shell_pid = %d", getpid()); //если команда не найдена то почему то два процесса идут, типа после execve надо захватывать статус выхода и дальше ничего не делать
	printf("\nall is made!!!\n");
	
	
	
	
	
	
	
	
	
	
	
	
	
//	big_str_print(vars.root_paths);
//	t_cmd *cmd = (*llst)->val;
//	char **args_str = convert_lst_to_str(cmd->args_lst);
//	big_str_print(args_str);
	
//	printf("%s\n", compose_cmd_args((*llst)->val, vars.root_paths));
//	printf("i = %d\n", ft_strncmp("PATH=", "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/go/bin:/usr/local/munki:/Library/Apple/usr/bin", 5));
//
//	printf("\n___________________________________________________________________________________________________________________________\n");
//	lst_print_tokens(huy);
//	big_str_print(vars.envp);
//	printf("\n___________________________________________________________________________________________________________________________\n");
	

//	root_paths_init(&vars);
//	big_str_print(vars.root_paths);
//    big_str_print(env);
//    char *kek = dollar_expansion(ft_strdup("ls > $a < aboba | > \"arbidol\" bruh | abobus  1 lol| denis no 3 | pop durak dope"), &vars);
//    dollar_parser(lst, vars);
    
//    printf("ret_str = %s", kek);
	
//	head = *huy;
	
	
    
//    lst_print_tokens(huy);
//	printf("pointer = {%p}\n", head->prev);
	
	
//	int i = 0;
	
//	while (head->key != PIPE)
//		head = head->next;
//	head = head->next;
//
//	while (head->key != PIPE)
//		head = head->next;
//	head = head->next;
	
//	head->prev = NULL; //пробую
	
//	printf("ok\n");
	
//	проверка работы llst_elem_new
	
//	while (i++ < 13)
//		head = head->next;
////	head = head->next;
//
//
//	printf("inserted head:\n");
//	lst_elem_print_token(head);
//
//
//	llst_elem = llst_elem_new(head);
//
//	printf("\n\nllst_elem:\n");
//	lst_print_tokens(llst_elem);
	
//	конец проверки работы llst_elem_new
	
	
	
//	проверка работы llst_new
	
	
//	llst = llst_new(huy);
//	head = *huy;
	
	
	
	
	
//	//начало теста на llst_elem_new и cmd_parser_______________
//	llst_elem = cmd_init();
//
//
//
////	is_null(NULL);
////	head = cmd_parser(head, llst_elem, llst_elem->val);
//	llst_elem = llst_elem_new(head);
//
//
//
//
//	t_cmd *cmd = llst_elem->val;
////	lst_elem_print_token(head);
////	printf("len = %d\n", lst_len(tmp));
//
//	tmp = cmd->files_in;
//	printf("files_in:\n");
//	lst_print_tokens(tmp);
//
//	tmp = cmd->files_out;
//	printf("files_out:\n");
//	lst_print_tokens(tmp);
////	lst_print_tokens(((t_cmd *)(llst_elem->val))->files_out);
//	//конец теста на llst_elem_new и cmd_parser_______________

	
	
	
	
	
	
	
	
	//начало теста на llst_new_______________
//	llst = llst_new(huy);



//	t_cmd *cmd = (*llst)->next->val;
////	lst_elem_print_token(head);
////	printf("len = %d\n", lst_len(tmp));
//
//	tmp = cmd->files_in;
//	printf("files_in:\n");
//	lst_print_tokens(tmp);
//
//	tmp = cmd->files_out;
//	printf("\nfiles_out:\n");
//	lst_print_tokens(tmp);
//
//	tmp = cmd->files_heredoc;
//	printf("\nfiles_heredoc:\n");
//	lst_print_tokens(tmp);
	
//	llst_cmd_n_elem_print(llst, 1);

//	lst_print_tokens(((t_cmd *)(llst_elem->val))->files_out);
	//конец теста на llst_new_______________


	
}

//
//int main(int argc, char **argv, char **env)
//{
//	t_vars	vars;
//	t_list **huy; //udalit'
//	t_list **test; //udalit'
//	t_list *head;
//
//	if (vars_initializing(&vars, env))
//		return (0);
////	while (!vars->exit_f)
////	{
////	}
////	printf("len = %d\n", big_str_len(env));
//	huy = bash_args_first_lst_init("aboba 12456 ");
////	head = *huy;
//	lst_print(huy);
////	test = lst_new(10);
//
////	printf("[[len = %d}}\n", lst_len(huy));
////	lst_clear(huy);
////	printf("{{{%d||||\n", head->key);
////	printf("lst_len = %d\n", lst_len(huy));
//}





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


