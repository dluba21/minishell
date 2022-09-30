#include "minishell.h"

int	ft_putstr_fd(char *s, int fd)
{
	if (s)
		return (write(fd, s, ft_strlen(s)));
	return (0);
}

int	ft_perror(char *str)
{
	perror(str);
	return (0);
}

int	ft_putendl_fd(char *s, int fd)
{
	int	ret;

	if (s)
	{
		ret = write(fd, s, ft_strlen(s)) + 1;
		write(fd, "\n", 1);
	}
	return (ret);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc(ft_strlen(str) + 1);
	if (ptr == NULL)
		return (NULL);
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (&ptr[0]);
}

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
