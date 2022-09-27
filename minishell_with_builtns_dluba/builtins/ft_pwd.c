#include "minishell1.h"

int	ft_pwd(t_vars *vars, t_cmd *cmd)
{
	char	*path;

	printf("built!\n");
	path = getcwd(NULL, 0);
	if (!path)
		return (1);
	ft_putendl_fd_(path, cmd->out_fd); // написать
	ft_free_line(&path); // написать
	return (0);
}
