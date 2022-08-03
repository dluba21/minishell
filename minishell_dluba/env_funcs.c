#include "minishell.h"

char **envp_new(t_vars **envp_lst) //создает новый массив переменных окуржения если в envp_lst были произведены изенеия (envp_f = 1)
{
	t_list	*head;
	char	**envp;
	char	**tmp;

	if (!envp_lst || !(*envp_lst))
		return (NULL);
	envp = (char **)malloc(sizeof(char *) * (lst_len(envp_lst) + 1));
	while (head)
	{
		*tmp++ = ft_strcpy(head->val);
		head = head->next;
	}
	*tmp = NULL;
	return (envp);
}
