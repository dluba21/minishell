#include "minishell.h"

void	lst_clear(t_list **lst)
{
	t_list *head;
	t_list *temp;

	head = *lst;
	while (head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
	free(temp); //correct?
	free(lst);
}

t_list	*lst_new_elem(void	*value, void *key) //создает один узел списка
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
	node->value = value;
	return (node);
}

int big_str_len(char **big_str) //cчитает длину двумерного массива
{
	int	i;

	i = 0;
	while (big_str[i])
		big_str[i++];
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
	head = lst;
	if (!head)
	{
		*lst = head;
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
	t_list	*head;

	lst = (t_list **)(malloc(sizeof(n)));
	node = lst_new_elem(envp[i]);
	if (!node)
		return ;
	*lst = node;
	head = *lst;
	i = 1;
	while (i < n)
	{
		node = lst_new_elem(0);
		if (!node)
			return ; //podpisat'
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

t_list	**lst_env_copy(char **envp); //делает список состоящий из envp
{
	char	**temp;
	t_list	**lst;
	t_list	*head;
	
	lst = lst_new(big_str_len(envp));
	if (!lst)
		return (NULL);
	temp = envp;
	head = *lst;
	while (*envp)
	{
		head->key = ENV_KEY; //дефайн сделать ENV_KEY или же вообще ключ не задавать
		head->val = *envp++;
		head = head->next;
	}
	return (lst);
}



//int main()
//{
//
//}
