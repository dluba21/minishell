#include "minishell.h"

char	*ft_readline(void)
{
	char *str;

	str = readline("\033[94m\033[49mminishell\033[0m$: ");
	if (!str)
		exit (0);
	add_history(str);
	return (str);
}
