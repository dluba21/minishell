#include "minishell.h"

int	lst_clear(t_list **lst)
{
	t_list *head;
	t_list *temp;

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

int lst_len(t_list **lst)
{
	int	i;
	t_list *temp;

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

void lst_push_back(t_list **lst, t_list *new_node)
{
	t_list *head;
	
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
	t_list *head;
	
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

t_list **lst_new(int n)
{
	int	i;
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

t_list	**lst_env_copy(char **envp)
{
	char	**temp;
	t_list	**lst;
	t_list	*node;
	
	lst = lst_new(0);
	if (!lst)
		return (NULL);
	temp = envp;
	while (*envp)
	{
		node = lst_elem_new(*envp++, 0);
		if (!node)
			return (NULL);
		lst_push_back(lst, node);
	}
	return (lst);
}


t_list *lst_get_last(t_list **lst)
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

t_list *lst_get_first(t_list *tail)
{
	if (!tail)
		return (NULL);
	while (tail->prev)
		tail = tail->prev;
	return (tail);
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

int 	lst_del_elem(t_list **lst, int n)
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

void	*ft_memcpy(void *src_0, int n)
{
	unsigned char	*dest;
	unsigned char	*src;

	src = src_0;
	dest = malloc(n);
	if (!src && !dest)
		return (NULL);
	while (n--)
		dest[n] = src[n];
	return (dest);
}
