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



void	recreate_envp(t_vars *vars)
{
	char	**tmp;

	tmp = vars->envp;
	vars->envp = convert_lst_to_str(vars->envp_lst);
	free_big_str(tmp);
}

void	env_var_trimmer(char *env_elem, char **buffer) // записывает в буфер все до '='
{
	char	*tmp;

	tmp = *buffer;
	while (*env_elem && *env_elem != '=')
		*tmp++ = *env_elem++;
	if (!*env_elem)
		printf("no '=' in envp\n"); //удалить, такое не бывает, наверное
	*tmp = 0;
}

char	*env_key_trimmer(char *env_elem)
{
	char	*key;
	char	*tmp;
	
//	if (ft_strchr(env_elem, "=") == ft_strlen(env_elem))
//		return (NULL);
	while (*env_elem && *env_elem != '=')
		env_elem++;
	env_elem++; // перешел за '='
	key =  (char *)malloc(ft_strlen(env_elem) + 1);
	if (!key)
		return (NULL);
	tmp = key;
	while (*env_elem)
		*tmp++ = *env_elem++;
	*tmp = 0;
	return (key);
}

char	*find_env_var(char *str, char **env) //ищет среди переменных окружения нужное или возвращает пустую строку если не нашло
{
	char	*buffer;
	char	*dollar_str;
	int		i;

	if (!env)
	{
		printf("error: no envp in dollar parser!\n");
		return (NULL);
	}
	dollar_str = NULL;
	buffer = ft_strset(100); // создает буфер
	while (*env)
	{
		env_var_trimmer(*env, &buffer);
		if (!ft_strcmp(str, buffer)) //если строки равны
		{
			dollar_str = env_key_trimmer(*env);
			break ;
		}
		env++;
	}
	free(buffer);
	if (!dollar_str) //если в итоге не нашло такую переменную
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
		tmp = env_key_trimmer((char *)head->val); //?
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
//			free(tmp);
//			free(head->val);
			head->val = ft_strjoin(new_key, "=");
			tmp = head->val;
			head->val = ft_strjoin(head->val, value);
//			free(value);
//			free(tmp);
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
