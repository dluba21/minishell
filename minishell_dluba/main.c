#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_vars	vars;
	t_list **huy; //udalit'
	t_list *head;
	t_list *head_2;
	t_list	**llst;
	t_list	**llst_elem;

//	if (vars_initializing(&vars, env))
//		return (0);
	
	
//	while (!vars->exit_f)
//	{
//	}
//	printf("len = %d\n", big_str_len(env));
	huy = bash_args_lst_lexer("<ls | cat >> | abobus  ");
//		huy = bash_args_first_lst_init(">>");
//	huy = bash_args_first_lst_init("aavabab\"asvasv\"");
	
	
	
	lst_print_tokens(huy);
	
//	llst = lst_elem_cmd_init(huy);

//	lst_print_tokens(llst_elem);
	head = *huy;
	head_2 = head;
//	while (head && head->key != PIPE)
//		head = head->next;
//	head = head->next;
//
//	llst = lst_elem_cmd_init(huy);
	llst = llst_elem_new(huy);
	printf("\n\n->->->->->->\n\n\n");
	lst_print_tokens(llst);
	
//	llst_elem = llst_elem_new(head_2);
	
//	while (llst_elem)
//	{
//		lst_elem_print_token(llst_elem);
//		llst_elem = llst_elem->next;
//	}
//	llst_elem = lst_new(1);
//	llst = lst_new(1);
	
//	head = *llst;
//	head->val = llst_elem;
	
//
//
//
//	llst_elem = llst_elem_new(head);
//	printf("\n\n->->->->->->\n\n\n");
//	while (llst_elem)
//	{
//		lst_elem_print_token(llst_elem);
//		llst_elem = llst_elem->next;
//	}
//	llst = llst_new(huy);
	
		
	
//	llst = llst_init(huy);
	
//	lst_elem_free(lst_get_last(huy));
	
	
//	lst_print(huy);
//	head = lst_get_last(huy);
	
//	lst_elem_print(head);
//	head = lst_get_first(head);
//	lst_elem_print(head);
//	printf("[[len = %d}}\n", lst_len(huy));
//	lst_clear(huy);
//	printf("{{{%d||||\n", head->key);
//	printf("lst_len = %d\n", lst_len(huy));
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
