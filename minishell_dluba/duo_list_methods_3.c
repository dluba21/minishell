#include "minishell.h"

t_list	*lst_get_last(t_list **lst)
{
	t_list	*head;

	if (!lst)
		return (NULL);
	head = *lst;
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_list	*lst_get_first(t_list *tail)
{
	if (!tail)
		return (NULL);
	while (tail->prev)
		tail = tail->prev;
	return (tail);
}
