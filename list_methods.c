#include "minishell.h"

int	lst_print(t_list **lst)
{
	t_list	*head;
	int		i;

	if (!lst)
		return (printf("no lst print error\n"));
	head = *lst;
	if (!head)
		return (printf("no elem print error\n"));
	i = 0;
	while (head)
	{
		printf("[%d] key = %d\tval = %s\n", i++, head->key, (char *)head->val);
		head = head->next;
	}
	return (0);
}

int	lst_elem_print(t_list *node)
{
	if (!node)
		return (printf("no node print error\n"));
	return (printf("key = %d\tval = %s\n", node->key, (char *)node->val));
}

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

t_list	*lst_new_elem(void	*value, int	key) //void *key хочу
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
	{
		printf("node malloc error\n");
		return (NULL);
	}
	node->next = NULL;
	node->key = key;
	node->val = value;
	return (node);
}

int big_str_len(char **big_str) //cчитает длину двумерного массива
{
	int	i;

	i = 0;
	while (big_str[i])
		i++;
	return (i);
}

int lst_len(t_list **lst) //возвращает длину списка
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

void lst_push_back(t_list **lst, t_list *new_node) //вставить в конце элемент
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
}

t_list **lst_new(int n) //создает список длины n
{
	int	i;
	t_list	**lst;
	t_list	*node;
//	t_list	*head;

	lst = (t_list **)(malloc(sizeof(n)));
	if (!lst)
		return (NULL);
//	node = lst_new_elem(NULL, 0);
//	if (!node)
//		return (NULL);
//	*lst = node;
//	head = *lst;
	i = 0;
	while (i < n)
	{
		node = lst_new_elem(NULL, 0);
		if (!node)
			return (NULL); //podpisat'
		lst_push_back(lst, node);
		i++;
	}
	return (lst);
}


//t_list **list_creator(int n) //создает список длины n
//{
//	int	i;
//	t_list	**lst;
//	t_list	*node;
//	t_list	*head;
//
//	lst = (t_list **)(malloc(sizeof(n)));
//	node = node_creator(envp[i]);
//	if (!node)
//		return ;
//	*lst = node;
//	head = *lst;
//	i = 1;
//	while (i < n)
//	{
//		node = node_creator(0);
//		if (!node)
//			return ; //podpisat'
//		head->next = node;
//		head = node;
//		i++;
//	}
//	return (lst);
//}

t_list	**lst_env_copy(char **envp) //делает список состоящий из envp
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
		node = lst_new_elem(*envp++, 0);
		if (!node)
			return (NULL);
		lst_push_back(lst, node);
	}
	return (lst);
}



//int main()
//{
//
//}
