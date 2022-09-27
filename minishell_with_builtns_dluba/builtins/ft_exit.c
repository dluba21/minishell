#include "minishell1.h"

int	is_num_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '-' && !ft_isdigit_(str[i]))
		{
			printf("minishell: exit: %s: numeric argument required\n", str);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_exit(t_vars *vars, t_cmd *cmd)
{
	size_t	len;
    int status;

	len = 0;
	printf("built!\n");
	if (!cmd) //что?
	{
		ft_putendl_fd_("\nexit", 1);
		exit(0);
		return (0);
	}
	while (cmd->args_array[len + 1])
		len++;
	if (len == 2)
	{
		if (!is_num_arg(cmd->args_array[2]))
			status = ft_atoi(cmd->args_array[2]);
	}
	if (len > 2)
		ft_putstr_fd_("minishell: exit: too many arguments\n", 2);
//	ft_free_mat(cmd->args_array); //?
	ft_putstr_fd_("exit\n", 1);
	exit(status);
	return (status);
}
