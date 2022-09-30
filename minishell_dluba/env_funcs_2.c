#include "minishell.h"

int	is_var_in_env(t_list **envp_lst, char *key)
{
	char	*tmp;
	t_list	*head;

	head = *envp_lst;
	while (head)
	{
		tmp = env_key_trimmer((char *)head->val);
		if (!ft_strcmp(tmp, key))
			return (1);
		head = head->next;
	}
	return (0);
}

void	change_env_val_key(t_vars *vars, char *old_key, \
							char *new_key, char *value)
{
	t_list	*head;
	char	*tmp;

	head = *(vars->envp_lst);
	while (head)
	{
		tmp = env_key_trimmer((char *)head->val);
		if (!ft_strcmp(old_key, tmp))
		{
			free(tmp);
			head->val = ft_strjoin(new_key, "=");
			tmp = head->val;
			head->val = ft_strjoin(head->val, value);
			free(tmp);
			break ;
		}
		free(tmp);
		head = head->next;
	}
	recreate_envp(vars);
}

void	add_env_value(t_vars *vars, char *key, char *value)
{
	char	*tmp;
	char	*new_env_elem;

	new_env_elem = ft_strjoin(key, "=");
	tmp = new_env_elem;
	new_env_elem = ft_strjoin(new_env_elem, value);
	lst_push_back(vars->envp_lst, lst_elem_new(new_env_elem, 0));
	free(tmp);
}

t_list	**lst_env_copy(char **envp)
{
	t_list	**lst;
	t_list	*node;

	lst = lst_new(0);
	if (!lst)
		return (NULL);
	while (*envp)
	{
		node = lst_elem_new(*envp++, 0);
		if (!node)
			return (NULL);
		lst_push_back(lst, node);
	}
	return (lst);
}
