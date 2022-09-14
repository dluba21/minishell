#include "minishell.h"

int		ft_env(char **ev, int out)
{
	size_t i;

	i = 0;
	if (!ev)
		return (-1);
	while (ev[i])
	{
		if (ft_strchr(ev[i], '='))
			ft_putendl_fd(ev[i], out); 
		i++;
	}
	return (0);
}