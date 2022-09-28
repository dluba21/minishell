#include "minishell1.h"


int	is_number_arg(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-' || !ft_isdigit(str[0]))
		return (0);
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}


int	ft_exit(t_vars *vars, t_cmd *cmd)
{
	if (lst_len(cmd->args_lst) > 2)
		return (ft_putstr_fd("exit: too many arguments\n", cmd->out_fd) * 0 + 1);
	if (lst_len(cmd->args_lst) == 1)
		exit (ft_putstr_fd("exit\n", cmd->out_fd) * 0);
	if (!is_number_arg(*cmd->args_array))
		exit (ft_putstr_fd("exit: %s numeric argument required\n", cmd->out_fd) * 0);
	exit(ft_atoi(*cmd->args_array + 1)); //?
}
