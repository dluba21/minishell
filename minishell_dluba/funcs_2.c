#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	find_spec_char(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])))
		i++;
	return (i);
}

char	*ft_strcpy(char *src)
{
	char	*str;
	int		n;
	int		i;

	n = ft_strlen(src);
	str = malloc(n + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = src[i];
		i++;
	}
	str[n] = 0;
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (-1);
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_strncmp(char *str_1, char *str_2, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (str_1[i] != str_2[i] || !str_1[i] || !str_2[i])
			return ((unsigned char)str_1[i] - (unsigned char)str_2[i]);
		i++;
	}
	return (0);
}
