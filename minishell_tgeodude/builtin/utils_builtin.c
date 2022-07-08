#include "minishell.h"

void	ft_putstr_fd(char *s, int fd) // удалить эту функцию и подключить ее из либы // нужна для того чтобы выводить строку через write
{
	int	i;

	i = -1;
	if (s)
		while (s[++i])
			write(fd, &s[i], 1);
}

int		ft_strcmp(char *s1, char *s2) // если нет в libft , то тогда оставить тут
{
	unsigned char	*str1;
	unsigned char	*str2;
	unsigned int	i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

size_t	ft_strlen(const char *s) // удалить и взять из libft
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}