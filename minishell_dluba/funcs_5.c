#include "minishell.h"

char	*ft_readline(void)
{
	char	*str;

	str = readline("\033[94m\033[49mminishell\033[0m$: ");
	if (!str)
		exit (0);
	add_history(str);
	return (str);
}

char	**convert_lst_to_str(t_list **lst)
{
	t_list	*head;
	char	**ret_str;
	char	**tmp;

	if (!lst || !(*lst))
		return (NULL);
	head = *lst;
	ret_str = (char **)malloc(sizeof(char *) * (lst_len(lst) + 1));
	tmp = ret_str;
	while (head)
	{
		*tmp++ = ft_strcpy(head->val);
		head = head->next;
	}
	*tmp = NULL;
	return (ret_str);
}
