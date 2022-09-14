#include "minishell.h"

char	**ft_del_env(char **ev, size_t env_count, char *el)
{
	int	i;
	int	j;
	char	**res;

	i = -1;
	j = 0;
	if (!el)
		return (ev);
	res = (char **)malloc(sizeof(char *) * env_count + 1);
	if (!res)
		return (NULL);
	while (++i < env_count)
	{
		if (ft_unstr(ev[i], el))
		{
			i++;
			continue;
		}
		res[j] = ft_strdup(ev[i]);
		i++;
		j++;
	}
	res[j] = NULL;
	ft_free_mat(ev);
	return (res);
}

char	**find_unset(char *arg, size_t *env_count, char **ev)
{
	int	j;

	j = -1;
	while (++j < *env_count)
	{
		if (ev[j] && ft_unstr(ev[j], arg))
		{
			ev = ft_del_env(ev, --(*env_count), arg);
			if (!ev)
				return (NULL);
			(*env_count)--;
			break ;
		}
	}
	return (ev);
}

int	unset_check(char *s)
{
	int	i;

	i = -1;
	while (++i, s[i])
		if (s[i] == '=' || ft_isdigit(s[0]))
			return (0 / printf("minishell: unset: `%s': not a valid identifier\n", s)); // заменить на свой printf
	return (1);
}

char    **ft_unset(t_cmd *cmd, char **ev)
{
    int     i;
    size_t  env_count;

    i = 0;
	env_count = 0;
	while (ev[env_count])
		env_count++;
    if (cmd->len_args == 1)
		return (ev);
    while (++i, cmd->len_args)
    {
        if (!unset_check(cmd->args[i]))
        {
            i++;
            continue;
        }
        if (!(ev = find_unset(cmd->args[i], &env_count, ev)))
			return (NULL);
    }
    return (ev);
}