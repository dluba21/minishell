#include "minishell1.h"

int		ft_env(t_vars *vars, t_cmd *cmd)
{
	size_t i;

	i = 0;
	if (!)
		return (-1);
	while (vars->envp[i])
	{
		if (ft_strchr_(vars->envp[i], '='))
			ft_putendl_fd_(vars->envp[i], cmd->out);
		i++;
	}
	return (0);
}
