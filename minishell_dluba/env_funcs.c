#include "minishell.h"

char **convert_lst_to_str(t_list **lst)
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



void	recreate_envp(t_vars *vars)
{
	char	**tmp;

	tmp = vars->envp;
	vars->envp = convert_lst_to_str(vars->envp_lst);
	free_big_str(tmp);
}

char	*env_key_trimmer(char *env_elem)
{
	char	*ret_str;
	char	*tmp;
	char	len;
	
	len = ft_strchr(env_elem, "=");
	if (len == ft_strlen(env_elem))
		return (NULL);
	ret_str = (char *)malloc(len + 1);
	tmp = ret_str;
	while (len--)
		*tmp++ = *env_elem++;
	*tmp = 0;
	return (ret_str);
}

char	*env_var_trimmer(char *env_elem)
{
	char	*key;
	char	*tmp;
	
	env_elem += ft_strchr(env_elem, "=") + 1;
	key = (char *)malloc(ft_strlen(env_elem) + 1);
	if (!key)
		return (NULL);
	tmp = key;
	while (*env_elem)
		*tmp++ = *env_elem++;
	*tmp = 0;
	return (key);
}

char	*find_env_var(char *str, char **env)
{
	char	*key;
	char	*dollar_str;
	int		i;

	if (!env)
	{
		printf("error: no envp in dollar parser!\n");
		return (NULL);
	}
	dollar_str = NULL;
	while (*env)
	{
		key = env_key_trimmer(*env);
		if (!ft_strcmp(str, key))
		{
			dollar_str = env_var_trimmer(*env);
			break ;
		}
		free(key);
		env++;
	}
	if (!dollar_str)
		return (NULL);
	return (dollar_str);
}

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

void	change_env_val_key(t_vars *vars, char *old_key, char *new_key, char *value)
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
