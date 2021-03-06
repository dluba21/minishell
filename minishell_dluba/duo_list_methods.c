#include "minishell.h"

//int l_print_tokens()

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

	char *tokens_array[10] = {"NILL", "WORD", "FIELD", "EXP_FIELD", "REDIR_OUT", "REDIR_IN", "REDIR_APPEND", "REDIR_HEREDOC", "PIPE", "SPACE"};
	if (!lst)
		return (printf("no lst print error\n"));
	head = *lst;
	if (!head)
		return (printf("no elem print error\n"));
	i = 0;
	while (head)
	{
		printf("[%d] key = %s\t\tval = %s\n", i++, tokens_array[head->key], (char *)head->val);
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
	char *tokens_array[10] = {"NILL", "WORD", "FIELD", "EXP_FIELD", "REDIR_OUT", "REDIR_IN", "REDIR_APPEND", "REDIR_HEREDOC", "PIPE", "SPACE"};

	if (!node)
		return (printf("no node print error\n"));
	return (printf("key = %s\tval = %s\n", tokens_array[node->key], (char *)node->val));
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

	lst = (t_list **)(malloc(sizeof(n)));
	*lst = NULL;
	if (!lst)
		return (NULL);
	i = -1;
	while (++i < n)
	{
		node = lst_elem_new(NULL, 0);
		if (!node)
			return (NULL); //podpisat'
		lst_push_back(lst, node);
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

t_list *lst_get_first(t_list *tail)  //хз зачем, просто написал
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
	new_elem = lst_elem_new(elem->val, elem->key); //надо перемаллочить val
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

void	llst_cmd_elem_print(t_list *llst_elem)
{

	if (!llst_elem)
	{
		printf("no llst elem!\n");
		return ;
	}
	if (!llst_elem->val)
	{
		printf("no cmd!\n");
		return ;
	}
	
	printf("cmd and args:\n");
	lst_print_tokens(((t_cmd *)(llst_elem->val))->args_lst);
	
	printf("files_in:\n");
	lst_print_tokens(((t_cmd *)(llst_elem->val))->files_in);

	printf("\nfiles_out:\n");
	lst_print_tokens(((t_cmd *)(llst_elem->val))->files_out);

	printf("\nfiles_heredoc:\n");
	lst_print_tokens(((t_cmd *)(llst_elem)->val)->files_heredoc);
}

	

void	llst_cmd_n_elem_print(t_list **llst, int n)
{
	t_list	*head;

	if (!llst)
	{
		printf("no llst!\n");
		return ;
	}
	if (!(*llst))
	{
		printf("no llst elem!\n");
		return ;
	}
	head = *llst;
	while (head && n--)
		head = head->next;
	if (!head)
	{
		printf("n more than len of llst!\n");
		return ;
	}
	llst_cmd_elem_print(head);
}

void	llst_cmd_print(t_list **llst)
{
	t_list	*head;
	int		i;

	if (!llst)
	{
		printf("no llst!\n");
		return ;
	}
	if (!(*llst))
	{
		printf("no llst elem!\n");
		return ;
	}
	head = *llst;
	i = 0;
	while (head)
	{
		printf("\n\tcmd = [%d]\n{\n", i);
		llst_cmd_elem_print(head);
		printf("}\n");
		head = head->next;
		i++;
	}
}
	
			
void	is_null(void *ptr)
{
	if (!ptr)
		printf("ptr = NULL\n");
	else
		printf("ptr = [%p]", ptr);
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
