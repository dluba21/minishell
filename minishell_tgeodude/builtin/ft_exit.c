#include "minishell.h"

int	is_num_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '-' && !ft_isdigit(str[i]))
		{
			ft_printf("minishell: exit: %s: numeric argument required\n", str);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_exit(t_cmd *cmd)
{
	size_t	len;
    int status;

	len = 0;
	if (!cmd)
	{
		ft_putendl_fd("\nexit", 1);
		exit(0);
		return (0);
	}
	while (cmd->args[len])
		len++;
	if (len == 2)
	{
		if (!is_num_arg(cmd->args[1]))
			status = ft_atoi(cmd->args[1]);
	}
	if (len > 2)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	ft_free_mat(cmd->args);
	ft_putstr_fd("exit\n", 1);
	exit(status);
	return (status);
}