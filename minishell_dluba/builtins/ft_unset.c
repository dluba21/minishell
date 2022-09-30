#include "../minishell.h"

int	ft_unset(t_vars *vars, t_cmd *cmd)
{
	t_list	*head;
	int		i;
	char	*key;

	if (lst_len(cmd->args_lst) == 1)
		return (0 / printf("unset: not enough arguments"));
	i = 0;
	while (cmd->args_array[++i])
	{
		head = *vars->envp_lst;
		while (head)
		{
			key = env_key_trimmer((char *)head->val);
			if (!ft_strcmp(key, cmd->args_array[i]))
				lst_elem_free(head);
			head = head->next;
			free(key);
		}
	}
	recreate_envp(vars);
	return (0);
}
