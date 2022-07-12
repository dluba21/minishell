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

int	lst_print_tokens(t_list **lst)
{
	t_list	*head;
	int		i;

	char *tokens_array[9] = {"WORD", "FIELD", "EXP_FIELD", "REDIR_OUT", "REDIR_IN", "REDIR_APPEND", "REDIR_HEREDOC", "PIPE", "SPACE"};
	if (!lst)
		return (printf("no lst print error\n"));
	head = *lst;
	if (!head)
		return (printf("no elem print error\n"));
	i = 0;
	while (head)
	{
		printf("[%d] key = %s\t\tval = %s\n", i++, tokens_array[head->key - 1], (char *)head->val);
		head = head->next;
	}
	printf("\n\n\n\n\n\n");
	return (0);
}

int	lst_elem_print(t_list *node)
{
	if (!node)
		return (printf("no node print error\n"));
	return (printf("key = %d\tval = %s\n", node->key, (char *)node->val));
}

int	lst_elem_print_token(t_list *node)
{
	char *tokens_array[9] = {"WORD", "FIELD", "EXP_FIELD", "REDIR_OUT", "REDIR_IN", "REDIR_APPEND", "REDIR_HEREDOC", "PIPE", "SPACE"};

	if (!node)
		return (printf("no node print error\n"));
	return (printf("key = %s\tval = %s\n", tokens_array[node->key - 1], (char *)node->val));
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

t_list	*lst_elem_new(void	*value, int	key) //void *key хочу
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
	new_node->prev = head;
}

void	lst_push_front(t_list **lst, t_list *new_node) //вставить в конце элемент
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
	new_node->prev = NULL; //мб убрать, поставил так как бесконечный
	*lst = new_node;
} //основное - надо было поменять голову и первый элемент->prev = NULL

t_list **lst_new(int n) //создает список длины n
{
	int	i;
	t_list	**lst;
	t_list	*node;
//	t_list	*head;

	lst = (t_list **)(malloc(sizeof(n)));
	if (!lst)
		return (NULL);
	i = 0;
	while (i < n)
	{
		node = lst_elem_new(NULL, 0);
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
		node = lst_elem_new(*envp++, 0);
		if (!node)
			return (NULL);
		lst_push_back(lst, node);
	}
	return (lst);
}


t_list *lst_get_last(t_list **lst) //хз зачем, просто написал
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

t_list *lst_get_first(t_list *tale)  //хз зачем, просто написал
{
	if (!tale)
		return (NULL);
	while (tale->prev)
		tale = tale->prev;
	return (tale);
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

//int main()
//{
//
//}

//надо сделать или двусвязный список чтобы удалять легко элементы или же добавить индексы порядка в элементы и сделать метод удаления по индексу

//до этого закольцовывалось в push_back, потому что при добавлении первого элемнта в список, prev != NULL, поэтому он доходил до начала списка и закольцовывал
