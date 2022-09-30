#include "minishell.h"

t_list	*cmd_lst_pusher(t_list *head_lst, t_list **lst, int key)
{
	head_lst = head_lst->next;
	head_lst->key = key;
	lst_push_back(lst, lst_elem_copy(head_lst));
	return (head_lst);
}

t_list	*cmd_parser(t_list *head_lst, t_cmd *cmd)
{
	if (head_lst->key == REDIR_IN)
		head_lst = cmd_lst_pusher(head_lst, cmd->files_in, REDIR_IN);
	else if (head_lst->key == REDIR_HEREDOC)
		head_lst = cmd_lst_pusher(head_lst, cmd->files_in, REDIR_HEREDOC);
	else if (head_lst->key == REDIR_OUT)
		head_lst = cmd_lst_pusher(head_lst, cmd->files_out, REDIR_OUT);
	else if (head_lst->key == REDIR_APPEND)
		head_lst = cmd_lst_pusher(head_lst, cmd->files_out, REDIR_APPEND);
	else if (head_lst->key == WORD)
		lst_push_back(cmd->args_lst, lst_elem_copy(head_lst));
	if (head_lst && head_lst->key != PIPE)
		head_lst = head_lst->next;
	return (head_lst);
}

int	check_pipes_redir(t_list *head)
{
	while (head)
	{
		if (head->key == PIPE)
		{
			if (!head->prev || head->prev->key == PIPE)
				return (1);
			if (!head->next | (head->next->key == PIPE))
				return (1);
		}
		if ((head->key == REDIR_APPEND || head->key == REDIR_OUT) && \
			(!head->next || head->next->key != WORD))
			return (1);
		if ((head->key == REDIR_HEREDOC || head->key == REDIR_OUT) && \
			(!head->next || head->next->key != WORD))
			return (1);
		head = head->next;
	}
	return (0);
}

t_list	*llst_elem_new(t_list *head_lst)
{
	t_list	*llst_elem;

	if (!head_lst)
		return (NULL);
	llst_elem = cmd_init();
	while (head_lst)
	{
		if (head_lst->key == PIPE)
			break ;
		head_lst = cmd_parser(head_lst, llst_elem->val);
	}
	return (llst_elem);
}

t_list	**llst_new(t_list **lst)
{
	t_list	**llst;
	t_list	*head_lst;
	t_list	*tmp;

	head_lst = *lst;
	if (!head_lst)
		return (NULL);
	if (check_pipes_redir(head_lst))
	{
		printf("pipe or redir syntax error\n");
		return (NULL);
	}
	llst = lst_new(0);
	while (head_lst)
	{
		tmp = head_lst;
		while (head_lst->next && head_lst->key != PIPE)
			head_lst = head_lst->next;
		lst_push_back(llst, llst_elem_new(tmp));
		head_lst = head_lst->next;
	}
	return (llst);
}
