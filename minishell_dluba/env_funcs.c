#include "minishell.h"

char **convert_lst_to_str(t_list **lst) //создает новый массив переменных окуржения если в envp_lst были произведены изенеия (envp_f = 1)
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
