#include "../minishell.h"

int	ft_pwd(t_vars *vars, t_cmd *cmd)
{
	char	*path;

	(void)vars;
	path = getcwd(NULL, 0);
	if (!path)
		return (1);
	ft_putendl_fd(path, cmd->out_fd);
	free(path);
	return (0);
}
