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

//	if (vars_initializing(&vars, env))
//		return (0);
	
	
//	while (!vars->exit_f)
//	{
//	}
//	printf("len = %d\n", big_str_len(env));
//	huy = bash_args_lst_lexer("<< kek << ls << norm azaz | > \"arbidol\" bruh | abobus  1 lol| denis no 3 | pop durak dope");
	huy = bash_args_lst_lexer("ls > kek < aboba | > \"arbidol\" bruh | abobus  1 lol| denis no 3 | pop durak dope");
//	huy = bash_args_lst_lexer("\'ls\'\"aboba\"|cat>aboba");
//	huy = bash_args_lst_lexer("12345"); //inf cycle
//	huy = bash_args_lst_lexer("\'ls\'\"12345\" cat"); //
	
//	huy = bash_args_lst_lexer("2|cat");
//	huy = bash_args_lst_lexer("ls|cat>aboba");
//		huy = bash_args_first_lst_init(">>");
//	huy = bash_args_first_lst_init("aavabab\"asvasv\"");
	
	
	
	lst_print_tokens(huy);
	
	printf("------------begin_list has written--------\n\n\n\n");
	
//	head = *huy;
	
	
	
	
//	printf("pointer = {%p}\n", head->prev);
	
	
	int i = 0;
	
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
	head = *huy;
	
	
	
	
	
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
	llst = llst_new(huy);



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
	
	llst_cmd_n_elem_print(llst, 0);

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
