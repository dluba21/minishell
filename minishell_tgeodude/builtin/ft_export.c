#include "minishell.h"

int		ft_unstr(char *var, char *key) // проверяет наличние совпадений
{
	size_t	i;
	size_t	var_len;
	size_t	key_len;

	i = 0;
	var_len = 0;
	key_len = 0;
	if (!var || !var[0] || !key)
		return (0);
	while (var[i] && key[i] && var[i] == key[i] && var[i] != '=')
		i++;
	while (var[var_len] && var[var_len] != '=')
		var_len++;
	while (key[key_len] && key[key_len] != '=')
		key_len++;
	if (key_len == i && key_len == var_len)
		return (1);
	return (0);
}

int find_value(char *args, char **ev) // проверяет наличние зачения
{
	int	i;

	i = -1;
	while (++i, ev[i])
		if (ft_unstr(ev[i], args))
			return(ev[i]);
	return (NULL);
}

char **change_value(char *var, char **ev) // изменяет если есть
{
	int	i;
	int	var_len;
	
	if (!var)
		return (NULL);
	var_len = 0;
	while (var[var_len] && var[var_len] != '=')
		var_len++;
	i = -1;
	while (++i, ev[i])
	{
		if (!ft_strncmp(var, ev[i], var_len))
		{
			ft_free_line(&ev[i]); // написать
			ev[i] = ft_strdup(var);
			return (ev);
		}
	}
	return (ev);
}

char	**add_value(char *var, char **ev) // добаляет если нет
{
	char	**evn;
	int		evn_count;
	int		i;

	if (!ev)
		return (NULL);
	evn_count = 0;
	while (ev[evn_count])
		++evn_count;
	evn = (char **)malloc(sizeof(char *) * (evn_count + 2));
	if (!evn)
		return (NULL);
	i = -1;
	while (++i, i < evn_count)
		evn[i] = ft_strdup(ev[i]);
	evn[i] = ft_strdup(var);
	evn[i + 1] = NULL;
	ft_free_mat(ev); // написать
	return (evn);
}

int	export_func(char *args, char **ev) // проверка переменной окружения
{
	int	i;

	i = 0;
	while (args[i] && args[i] != '=')
		i++;
	if ((!args[i] || args[i] == '=') && !find_value(args, ev))
		return (1);
	if (args[i] == '=' && find_value(args, ev))
		return (2);
	return(0);
}

char	**ft_export(t_cmd *cmd, char **ev) // добавляет или изменяет переменную окружения
{
	int	i;
	int	find;

	i = -1;
	while(++i, i < cmd->len_args)
	{
		find = export_func(cmd->args[i], ev);
		if (find == 1)
			ev = add_value(cmd->args[i], ev);
		else if (find == 2)
			ev = change_value();
	}
	return (ev);
}