#include "minishell1.h"
	
int		ft_env(t_vars *vars, t_cmd *cmd)
{
	t_list	*head;
	int		n;

	if (!vars->envp_lst)
		return (-1);
	head = *vars->envp_lst;
	while (head)
	{
//		n = ft_strchr((char *)head->val, '=');
//		if (n != ft_strlen((char *)head->val))
		ft_putendl_fd((char *)head->val + n, cmd->out_fd); //?
//		head = head->next;
	}
	return (0);
}
