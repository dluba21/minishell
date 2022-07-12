#include "minishell.h"

t_list	**llst_elem_new(t_list **lst)
{
	t_list	**llst_elem;
	t_list	*head_llst_elem;
	t_list	*tmp;
	t_list	*head_lst;

	if (!lst)
		return (NULL);
	head_lst = *lst;
	if (!head_lst)
		return (NULL);
	llst_elem = lst_new(0);
//	llist_elem = head_lst; // сохраняем голову
	while (head_lst && head_lst->key != PIPE)
		head_lst = head_lst->next;
	if (head_lst) //если на пайп зашло к не конец
		head_lst->next = NULL;
	while (head_lst)
	{
		tmp = head_lst;
		head_lst = head_lst->prev;
		lst_push_front(llst_elem, tmp);
	}
	return (llst_elem);
}


//
//t_list	**llst_new(t_list	**lst) //список списков команд и пайпов
//{
//	t_list	**llst;
//	t_list	**llist_elem;
//	t_list	*head_lst;
//	t_list	*head_llst;
//	t_list	*tmp;
////	if (check_pipes == -1)
////		exit(printf("pipe syntax error\n"));
//	head_lst = *lst;
//
//	if (!head_lst)
//		return (NULL);
//	llst = lst_new(1);
//	head_llst = *llst;
//	while (head_lst)
//	{
//		tmp = head_lst; //сохраняю голову
//		while (head_lst && head_lst->key != PIPE)
//			head_lst = head_lst->next;
//		head_llst->val = llst_elem_new(tmp);
//		if (head_lst) //если не конец еще и встретился пайп
//		{
//			head_lst = head_lst->next; //пропускаем пайп
//			head_llst = head_llst->next;
//		}
//	}
//	//мб head_lst сразу ноль(проверка на один случай)
////	head_llst->next = NULL;
//	return (llst);
//}



//int	check_pipes(t_list **lst)
//{
//	t_list	*head_old_lst;
//	t_list	*head_llst; //голова логического списка
//	t_list	**logic_lst;
//	t_list	**lst_elem; //элемент логического списка
//
//	if (!lst)
//		return (-1);
//	head_lst = *lst;
//	if (!head_old_lst)
//		return (-1);
//	while (head_old_lst)
//	{
//		lst_elem = lst_init(0); //создаем элемент логического списка
//		head_llst = *lst_elem;
//		while (head_old_lst->key != PIPE)
//		{
//			head_llst = head_old_lst;
//			head_llst = head_llst->next;
//			head_old_lst = head_old_lst->next;
//		}
//
//		head_old_lst = head_old_lst->next; //пропускаю пайп
//	}
//	while (head)
//	{
//
//		if ()
//
//		head = head->next
//	}
//
//
//}





//t_list **bash_args_lst_parser(t_list **lst)
//{
//	t_list	*head;
//
//	if (!lst)
//	{
//		printf("no lst in parser\n");
//		return (NULL);
//	}
//	head = *lst;
//	if (!head)
//	{
//		printf("no elem in parser\n");
//		return (NULL);
//	}
//	while (head)
//	{
//		
//		find_redirects_etc();
//		head = head->next;
//	}
//	
//}

//логический список состоит из голов списков команд (все что между пайпами)
//нельзя головы, походу придется копировать списки и маллочить все заново и делать структуру логического списка, где списик в составе
//надо было делать как раньше, то есть хранятся списки в логическом списке, маллочить только надо было

//сначала чек на синтаксис пайпов, потом создаю список списков

//доллар обработать
//структуру команд сделать
//метод, который список разделяет на подсписки для пайпов
//проверка синтаксиса пайпов
//мб cat | < aboba
