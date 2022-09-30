#include "minishell.h"

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
