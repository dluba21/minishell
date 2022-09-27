#include "minishell1.h"

int		ft_env(t_vars *vars, t_cmd *cmd)
{
	size_t i;

	i = 0; //i = -1??
	if (!vars->envp)
		return (-1);
	while (vars->envp[i])
	{
		if (ft_strchr_(vars->envp[i], '='))
			ft_putendl_fd_(vars->envp[i], cmd->out_fd);
		i++;
	}
	return (0);
}
