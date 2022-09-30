#include "minishell.h"

t_list	*lst_elem_copy(t_list *elem)
{
	t_list	*new_elem;

	if (!elem)
		return (NULL);
	new_elem = lst_elem_new(elem->val, elem->key);
	if (!new_elem)
		return (NULL);
	return (new_elem);
}

int	lst_del_elem(t_list **lst, int n)
{
	t_list	*head;

	if (!lst && !(*lst))
		return (printf("lst_del error: no lst\n"));
	head = *lst;
	while (head && n--)
		head = head->next;
	lst_elem_free(head);
	return (0);
}

int	lst_elem_free(t_list *node)
{
	if (!node)
		return (printf("lst_free error: no elem\n"));
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	return (0);
}

int	lst_clear(t_list **lst)
{
	t_list	*head;
	t_list	*temp;

	if (!lst)
		return (printf("free error: no list\n"));
	head = *lst;
	while (head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
	free(lst);
	return (0);
}
