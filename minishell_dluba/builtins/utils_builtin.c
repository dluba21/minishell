#include "minishell1.h"

void	ft_putstr_fd_(char *s, int fd) // удалить эту функцию и подключить ее из либы // нужна для того чтобы выводить строку через write
{
	int	i;

	i = -1;
	if (s)
		while (s[++i])
			write(fd, &s[i], 1);
}

int		ft_strcmp_(char *s1, char *s2) // если нет в libft , то тогда оставить тут
{
	unsigned char	*str1;
	unsigned char	*str2;
	unsigned int	i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (ft_strlen_(s1) != ft_strlen_(s2))
		return (-1);
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

size_t	ft_strlen_(const char *s) // удалить и взять из libft
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup_(const char *s) // удалить и взять из libft
{
	char	*s2;
	size_t	i;

	i = -1;
	s2 = malloc(ft_strlen_(s) + 1);
	if (!s2)
		return (NULL);
	while (i++, s[i])
		s2[i] = s[i];
	s2[i] = '\0';
	return (s2);
}

int	ft_strncmp_(const char *s1, const char *s2, size_t n) // удалить и взять из libft
{
	size_t	i;

	i = -1;
	if (!n)
		return (0);
	while (i++, (s1[i] != 0 || s2[i] != 0) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		if (s1[i + 1] == 0 && s2[i + 1] != 0 && i != (n - 1))
			return (0 - (unsigned char) s1[i]);
		if (s1[i + 1] != 0 && s2[i + 1] == 0 && i != (n - 1))
			return ((unsigned char) s1[i] - 0);
	}
	return (0);
}

int	ft_isdigit_(int c) // удалить и взять из libft
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_putendl_fd_(char *s, int fd) // удалить и взять из либы
{
	if (s)
	{
		while (*s)
		{
			write(fd, s, 1);
			s++;
		}
		write(fd, "\n", 1);
	}
}

char	**ft_free_mat(char **mat)
{
	int i;

	i = 0;
	if (!mat)
		return (NULL);
	while (mat[i])
	{
		ft_free_line(&mat[i]);
		i++;
	}
	free(mat);
	mat = NULL;
	return (mat);
}

void	ft_free_line(char **line)
{
	free(*line);
	*line = NULL;
}

char	*ft_strjoin_(char const *s1, char const *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	s3 = (char *)malloc((ft_strlen_(s1) + ft_strlen_(s2)) + 1);
	if (!s3)
		return (NULL);
	i = -1;
	j = -1;
	while (i++, s1[i])
		s3[i] = s1[i];
	while (j++, s2[j])
	{
		s3[i] = s2[j];
		i++;
	}
	s3[i] = 0;
	return (s3);
}

char	*ft_var_find(char *var, char **ev)
{
	size_t	i;
	char	*value;
	char	*res;
	int		var_len;

	/* if (ft_strcmp(var, "?") == 0)
		return (ft_itoa(g_shell.status)); */
	i = 0;
	var_len = ft_strlen_(var);
	if (!var || !ev)
		return (NULL);
	while (ev[i])
	{
		if (!ft_strncmp_(var, ev[i], var_len) && ev[i][var_len] == '=')
		{
			value = ft_strchr_(ev[i], '=');
			if (!value)
				return (NULL);
			value++;
			res = ft_strdup_(value);
			return (res);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strchr_(const char *string, int symbol) // из либы
{
	unsigned char	tmp;

	tmp = symbol;
	while (*string)
	{
		if (*string == tmp)
			return ((char *)string);
		string++;
	}
	if (symbol == '\0')
		return ((char *)(string + ft_strlen_(string)));
	return (0);
}

char		*ft_find_env(char *key, char **ev)
{
	size_t i;
	size_t len_env;

	i = 0;
	len_env = 0;
	while (ev[len_env])
		len_env++;
	if (!key)
		return (NULL);
	while (i < len_env)
	{
		if (ft_strnstr_(ev[i], key, ft_strlen_(key)))
			return (ev[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strnstr_(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (++i < len && haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			while (needle[j] == haystack[i + j]
				&& i + j < len && haystack[i + j])
			{
				if (!needle[j + 1])
					return ((char *)(haystack + i));
				j++;
			}
		}
	}
	return (0);
}
