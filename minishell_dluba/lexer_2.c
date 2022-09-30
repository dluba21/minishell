#include "minishell.h"

char	*quote_str_trim(char *bash_str, char *sym_arr)
{
	int		len;
	int		i;
	char	*trimmed_str;

	len = ft_strchr(bash_str, sym_arr);
	trimmed_str = (char *)(malloc(len + 1));
	if (!trimmed_str)
		return (NULL);
	i = 0;
	while (i < len)
		trimmed_str[i++] = *bash_str++;
	trimmed_str[i] = 0;
	return (trimmed_str);
}
