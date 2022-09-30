#include "minishell.h"

t_list	*lst_elem_new(void *value, int key)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
	{
		printf("node malloc error\n");
		return (NULL);
	}
	node->next = NULL;
	node->prev = NULL;
	node->key = key;
	node->val = value;
	return (node);
}

int	lst_len(t_list **lst)
{
	int		i;
	t_list	*temp;

	if (!lst)
		return (0);
	temp = *lst;
	if (!temp)
		return (0);
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	lst_push_back(t_list **lst, t_list *new_node)
{
	t_list	*head;

	if (!lst || !new_node)
		return ;
	head = *lst;
	if (!head)
	{
		*lst = new_node;
		return ;
	}
	while (head->next)
		head = head->next;
	head->next = new_node;
	new_node->prev = head;
}

void	lst_push_front(t_list **lst, t_list *new_node)
{
	t_list	*head;

	if (!lst || !new_node)
		return ;
	head = *lst;
	if (!head)
	{
		*lst = new_node;
		new_node->next = NULL;
		new_node->prev = NULL;
		return ;
	}
	while (head->prev)
		head = head->prev;
	head->prev = new_node;
	new_node->next = head;
	new_node->prev = NULL;
	*lst = new_node;
}

t_list	**lst_new(int n)
{
	int		i;
	t_list	**lst;
	t_list	*node;

	lst = (t_list **)(malloc(sizeof(n)));
	*lst = NULL;
	if (!lst)
		return (NULL);
	i = -1;
	while (++i < n)
	{
		node = lst_elem_new(NULL, 0);
		if (!node)
			return (NULL);
		lst_push_back(lst, node);
	}
	return (lst);
}
