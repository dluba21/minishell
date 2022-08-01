#include "minishell.h"

t_list	*cmd_init(void) //мб возвращать cmd а внешне присваивать уже lst_elem_val = cmd?
{
	t_list	*lst_elem;
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->files_in = lst_new(0); //как их фришить если будет execve?
	cmd->files_out = lst_new(0);
	cmd->files_heredoc = lst_new(0);
	cmd->args_lst = lst_new(0); //уже в execve сделаю char **
	cmd->args_array = NULL; //потом сделать
	cmd->vars = NULL; //потом прикрепить

	//не совсем верно
	if (!cmd->files_in || !cmd->files_out || \
		!cmd->files_heredoc || !cmd->args_lst)
		return (NULL);
	lst_elem = lst_elem_new(cmd, 0);
	if (!lst_elem)
		return (NULL);
	return (lst_elem);
}


t_list	*cmd_parser(t_list *head_lst, t_list *llst_elem, t_cmd *cmd) //двигает внутри голову дальше и заносит элементы в список
{ //мб еще сделать внутри структуры команды флаг - маску на heredoc и редиректы, а также права на append или trunc, короче int - как раз 4 бита
	//поменяется ли после функции llst_elem?

//	t_cmd *cmd = llst_elem->val; //мб подать в ф-цию cmd? //или же добавить структуру с cmd чтобы список напрямую составлять
	if (head_lst->key == REDIR_IN)
	{
		head_lst = head_lst->next;
		lst_push_back(cmd->files_in, lst_elem_copy(head_lst));
	}
	else if (head_lst->key == REDIR_HEREDOC)
	{
		head_lst = head_lst->next;
		lst_push_back(cmd->files_heredoc, lst_elem_copy(head_lst));
	}
	else if (head_lst->key == REDIR_OUT)
	{
		head_lst = head_lst->next;
		lst_push_back(cmd->files_out, lst_elem_copy(head_lst));
	}
	else if (head_lst->key == REDIR_APPEND) //сделать флаг
	{
		head_lst = head_lst->next;
		lst_push_back(cmd->files_out, lst_elem_copy(head_lst));
	}
	else if (head_lst->key == WORD || head_lst->key == EXP_FIELD || head_lst->key == FIELD) //команда и заполнение аргументов //чекуть как исправить ls >> aboba kek
		lst_push_back(cmd->args_lst, lst_elem_copy(head_lst));

	if (head_lst && head_lst->key != PIPE) //переходим к следующему слову, если не конец и не пайп
		head_lst = head_lst->next;
//	printf("---------->\n");
////	lst_print_tokens(cmd->files_out);
//	printf("len_lst = %d\n", lst_len(cmd->files_out));
//	printf("<----------\n");
	
	
	//будто обновляется каждый раз cmd
	return (head_lst);
}

int	check_pipes(t_list *head)
{
	while (head)
	{
		if (head->key == PIPE)
		{
			if (!head->prev || (head->prev && head->prev->key == PIPE))
				return (1);
			if (!head->next || (head->next && head->next->key == PIPE))
				return (1);
		}
		head = head->next;
	}
	return (0);
}

t_list	*llst_elem_new(t_list *head_lst) //задел на бонус
{
	t_list	*llst_elem;
	t_list	*tmp;


	if (!head_lst)
		return (NULL);
	llst_elem = cmd_init();
	while (head_lst)
	{
		if (head_lst->key == PIPE)
			break;
		head_lst = cmd_parser(head_lst, llst_elem, llst_elem->val);
	}
	
	t_cmd *cmd_1 = llst_elem->val;

//	lst_print_tokens(cmd->files_out);
//	printf("len_lst = %d\n", lst_len(cmd->files_out));
//	printf("<----------\n");
//	printf("\n\n\n\n\n\n");
//		printf("---------->\n");
//	lst_print_tokens(cmd_1->files_out);
	return (llst_elem);
}





//
//t_list	**llst_elem_new(t_list *head_lst) //задел на бонус
//{
//	t_list	**llst_elem;
//	t_list	*head_llst_elem;
//	t_list	*tmp;
//
//
//	if (!head_lst)
//		return (NULL);
//	llst_elem = lst_new(0);
//	while (head_lst)
//	{
//		if (head_lst->key == PIPE)
//			break;
//		lst_push_back(llst_elem, lst_elem_copy(head_lst));
//		head_lst = head_lst->next;
//	}
////	if (head_lst && head_lst->key != PIPE) //не добавлял последний элемент раньше
////		lst_push_back(llst_elem, lst_elem_copy(head_lst));
//	return (llst_elem);
//}

t_list	**llst_new(t_list	**lst) //задел на бонус: список списков команд и пайпов
{
	t_list	**llst;
	t_list	**llist_elem;
	t_list	*head_lst;
	t_list	*tmp;
	
//	if (check_pipes == -1)
//		exit(printf("pipe syntax error\n"));
	head_lst = *lst;

	if (!head_lst)
		return (NULL);
	if (check_pipes(head_lst)) //тут || и | | не различаются (без бонусов норм)
	{
		printf("pipe error\n");
		return (NULL); //зафришить все говно
	}
	llst = lst_new(0);
	while (head_lst)
	{
		tmp = head_lst; //сохраняю голову
		while (head_lst->next && head_lst->key != PIPE)  //head_lst->next
			head_lst = head_lst->next;
		
		lst_push_back(llst, llst_elem_new(tmp));
//		if (head_lst) //если не конец еще и встретился пайп
		head_lst = head_lst->next; //пропускаем пайп
	}
	
//	t_list *head = *llst;
//	t_cmd *cmd = head->val;
//	t_list **kek = cmd->files_out;
//	t_list	*head_2 = *kek;
////	lst_elem_print_token(head_2);
//	if (head_lst && head_lst->key == PIPE)
//		printf("error\n");
	//мб head_lst сразу ноль(проверка на один случай)
	return (llst);
}
//
//t_list	**llst_new(t_list	**lst) //задел на бонус: список списков команд и пайпов
//{
//	t_list	**llst;
//	t_list	**llist_elem;
//	t_list	*head_lst;
//	t_list	*tmp;
//	
////	if (check_pipes == -1)
////		exit(printf("pipe syntax error\n"));
//	head_lst = *lst;
//
//	if (!head_lst)
//		return (NULL);
//	llst = lst_new(0);
//	while (head_lst)
//	{
//		tmp = head_lst; //сохраняю голову
//		while (head_lst->next && head_lst->key != PIPE)  //head_lst->next
//			head_lst = head_lst->next;
//		if (head_lst->key == PIPE && !head_lst->next)
//			exit(printf("error: pipe at the end of the string\n")); //исправить от ликов надо
//		lst_push_back(llst, lst_elem_new(llst_elem_new(tmp), 0));
////		if (head_lst) //если не конец еще и встретился пайп
//		head_lst = head_lst->next; //пропускаем пайп
//	}
////	if (head_lst && head_lst->key == PIPE)
////		printf("error\n");
//	//мб head_lst сразу ноль(проверка на один случай)
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




//логический список состоит из голов списков команд (все что между пайпами)
//нельзя головы, походу придется копировать списки и маллочить все заново и делать структуру логического списка, где списик в составе
//надо было делать как раньше, то есть хранятся списки в логическом списке, маллочить только надо было

//сначала чек на синтаксис пайпов, потом создаю список списков

//доллар обработать
//структуру команд сделать
//метод, который список разделяет на подсписки для пайпов
//проверка синтаксиса пайпов
//мб cat | < aboba


//алгос: запоминаю голову в начале, иду до пайпа, затем идет создание списка с головы до встреченного пайпа, затем пайп пропускается, снова запоминаю голову и иду до следующего пайпа... затем запомнил после последнего пайпа голову и иду до конца строки и снова делаю список их оставшегося до конца строки
 

//мб просто легче втупую скопировать и идти последовательно зато, а не туда сюда
