#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_vars	vars;
	t_list **huy; //udalit'
	t_list *head;
	t_list *head_2;
	t_list *head_3;
	t_list *tmp;
	t_list	**llst;
	t_list	**llst_elem;

//	if (vars_initializing(&vars, env))
//		return (0);
	
	
//	while (!vars->exit_f)
//	{
//	}
//	printf("len = %d\n", big_str_len(env));
	huy = bash_args_lst_lexer("ls | \"arbidol\" bruh | abobus  1 lol| denis no 3 | pop durak dope");
//		huy = bash_args_first_lst_init(">>");
//	huy = bash_args_first_lst_init("aavabab\"asvasv\"");
	
	
	
	lst_print_tokens(huy);
	
	printf("------------begin_list has written--------\n\n\n\n");
	
	head = *huy;
	
	
	
	
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
	
	
	
	//проверка работы llst_elem_new
//	while (i++ < 24)
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
	
	//конец проверки работы llst_elem_new
	
	
//	llst = lst_new(0);
	t_list **tmp_llst;
	head_3 = *llst;
	tmp_llst = head_3->val;
	head_2 = *tmp_llst;
	while (head_2)
	{
		i++;
		head_2 = head_2->next;
	}
	printf("len = %d\n", i);
	
	
//	head_2 = head;
////	printf("\n\n\n->\n");
////	lst_elem_print_token(head_2);
////	printf("\n<-\n\n\n");
//	while (head && head->key != PIPE)
//		head = head->next;
//	head = head->next;
////
//
//	lst_push_back(llst, lst_elem_new(llst_elem_new(head_2), 0));
//	lst_print_tokens(llst_elem_new(head_2));
//
//
//
//	head_2 = head;
//	while (head->key != PIPE)
//		head = head->next;
//	head = head->next;
//
////	printf("\n\n\n->\n");
////	lst_elem_print_token(head_2);
////	printf("\n<-\n\n\n");
//
//	lst_push_back(llst, lst_elem_new(llst_elem_new(head_2), 0));
//	lst_print_tokens(llst_elem_new(head_2));
//
//
//
//	head_2 = head;
//	while (head->key != PIPE)
//		head = head->next;
//	head = head->next;
//
////	printf("\n\n\n->\n");
////	lst_elem_print_token(head_2);
////	printf("\n<-\n\n\n");
//
//	lst_push_back(llst, lst_elem_new(llst_elem_new(head_2), 0));
//	lst_print_tokens(llst_elem_new(head_2));
//
//
//
//	head_2 = head;
//	while (head->next)
//		head = head->next;
////	head = head->next;
//
////	printf("\n\n\n->\n");
////	lst_elem_print_token(head_2);
////	printf("\n<-\n\n\n");
//
//	lst_push_back(llst, lst_elem_new(llst_elem_new(head_2), 0));
//	lst_print_tokens(llst_elem_new(head_2));

	
//
//
//
//
//
//	t_list *head_3 = *llst;
	

//	i = 0;
//	printf("-----------------------------------\n");
//	while (head_3)
//	{
//		printf("[%d]:\n", i);
//		lst_print_tokens(head_3->val);
////				printf("[%d]\n", head_3->key);
//		head_3 = head_3->next;
//		printf("\n\n->->->->->->\n\n\n");
//
//		i++;
//	}
//	printf("len_llst = %d\n", i);
	
////
	
	
	
	
	
	
	
////	llst = lst_elem_cmd_init(huy);
	
	
	
//	llst_elem = lst_new(1);
//	llst =  lst_new(1);
//	llst->key = llst_elem;
	
//
//	head = *llst;
//	head->val = llst_elem;
//
	

//	llst = llst_elem_new(head);
//	llst = llst_new(huy);
//	lst_print_tokens(llst);

//	head->next = NULL;
//	printf("i = %d\n", i);
//	lst_elem_print_token(head);
//	i = 0;
//	printf("{%p}\n", head);
		
	
	
	
//	tmp = head;
//	head = head->prev;
//	lst_push_front(llst, tmp);
//
//
//	tmp = head;
//	head = head->prev;
//	lst_push_front(llst, tmp);
//
//	tmp = head;
//	head = head->prev;
//	lst_push_front(llst, tmp);
//
//	lst_print_tokens(llst);
//	while (head)
//	{
//
////		lst_elem_print_token(head);
//		tmp = head;
//		head = head->prev;
//		lst_push_front(llst, tmp);
//	
////		i++;
//	}
//	printf("\n\n->->->->->->\n\n\n");
//	lst_print_tokens(llst);
//	printf("{%d}\n", i);
//	lst_push_front(llst, head);
//	head->next = NULL;
//	head_2 = *llst;

//	llst = llst_elem_new(huy);

//	lst_print_tokens(llst);
	
	
////	llst_elem = llst_elem_new(head_2);
//
////	while (llst_elem)
////	{
////		lst_elem_print_token(llst_elem);
////		llst_elem = llst_elem->next;
////	}

	
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

