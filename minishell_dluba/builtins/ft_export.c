#include "minishell1.h"

//int		ft_unstr(char *var, char *key) // проверяет наличние совпадений
//{
//	size_t	i;
//	size_t	var_len;
//	size_t	key_len;
//
//	i = 0;
//	var_len = 0;
//	key_len = 0;
//	if (!var || !var[0] || !key)
//		return (0);
//	while (var[i] && key[i] && var[i] == key[i] && var[i] != '=')
//		i++;
//	while (var[var_len] && var[var_len] != '=')
//		var_len++;
//	while (key[key_len] && key[key_len] != '=')
//		key_len++;
//	if (key_len == i && key_len == var_len)
//		return (1);
//	return (0);
//}
//
//int find_value(char *args, char **ev) // проверяет наличние зачения
//{
//	int	i;
//
//	i = -1;
//	while (++i, ev[i])
//		if (ft_unstr(ev[i], args))
//			return(1); //return(ev[i]); что это?
//	return (0); //return (NULL); что это?
//}
//
//char **change_value(char *var, char **ev) // изменяет если есть
//{
//	int	i;
//	int	var_len;
//
//	if (!var)
//		return (NULL);
//	var_len = 0;
//	while (var[var_len] && var[var_len] != '=')
//		var_len++;
//	i = -1;
//	while (++i, ev[i])
//	{
//		if (!ft_strncmp_(var, ev[i], var_len))
//		{
//			ft_free_line(&ev[i]); // написать
//			ev[i] = ft_strdup_(var);
//			return (ev);
//		}
//	}
//	return (ev);
//}
//
//char	**add_value(char *var, char **ev) // добаляет если нет
//{
//	char	**evn;
//	int		evn_count;
//	int		i;
//
//	if (!ev)
//		return (NULL);
//	evn_count = 0;
//	while (ev[evn_count])
//		++evn_count;
//	evn = (char **)malloc(sizeof(char *) * (evn_count + 2));
//	if (!evn)
//		return (NULL);
//	i = -1;
//	while (++i, i < evn_count)
//		evn[i] = ft_strdup_(ev[i]);
//	evn[i] = ft_strdup_(var);
//	evn[i + 1] = NULL;
//	ft_free_mat(ev); // написать
//	return (evn);
//}
//
//int	export_func(char *args, char **ev) // проверка переменной окружения
//{
//	int	i;
//
//	i = 0;
//	while (args[i] && args[i] != '=')
//		i++;
//	if ((!args[i] || args[i] == '=') && !find_value(args, ev))
//		return (1);
//	if (args[i] == '=' && find_value(args, ev))
//		return (2);
//	return(0);
//}

//int	ft_export(t_vars *vars, t_cmd *cmd) // добавляет или изменяет переменную окружения
//{
//	int	i;
//	int	find;
//
//	i = -1;
//	printf("built!\n");
//	while(++i, i  < cmd->len_args - 1)
//	{
//		find = export_func(cmd->args_array[i + 1], vars->envp);
//		if (find == 1)
//			vars->envp = add_value(cmd->args_array[i + 1], vars->envp);
//		else if (find == 2)
//			vars->envp = change_value(cmd->args_array[i + 1], vars->envp);
//	}
//	return (0);
//}

int	ft_export(t_vars *vars, t_cmd *cmd) // добавляет или изменяет переменную окружения
{
	int		i;
	char	*key;
	char	*value;
	char	*var;

	if (lst_len(cmd->args_lst) == 1)
		return (0 / printf("unset: not enough arguments"));
	i = 0;
	while (cmd->args_array[++i])
	{
		key = env_key_trimmer(cmd->args_array[i]);
		if (key)
		{
			var = env_var_trimmer(cmd->args_array[i]);
			if (is_var_in_env(vars->envp_lst, key))
				change_env_val_key(vars, key, key, var);
			else
				add_env_value(vars, key, var);
			free(var);
		}
		free(key);
	}
	recreate_envp(vars);
	return (0);
}



