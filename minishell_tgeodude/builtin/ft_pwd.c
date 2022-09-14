#include "minishell.h"

int	ft_pwd(int out)
{
	char *path;

	path = getcwd(NULL, 0);
	if (!path)
		return (1);
	ft_putendl_fd(path, out); // написать
	ft_free_line(&path); // написать
	return (0);
}