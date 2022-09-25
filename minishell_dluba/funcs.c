#include "minishell.h"

int ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		i++;
	return (i);
}


static char	*blank_kostyl(void)
{
	char	*s1;

	s1 = malloc(sizeof(char));
	if (!s1)
		return (NULL);
	s1[0] = '\0';
	return (s1);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*s1;
	int		i;
	int		str_len;

	i = 0;
	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (blank_kostyl());
	if (start + len > str_len)
		len = str_len - start;
	s1 = (char *)malloc(len + 1);
	if (!s1)
		return (NULL);
	if (start < str_len || (len + start) <= str_len)
	{
		while (i < len)
			s1[i++] = s[start++];
	}
	s1[i] = '\0';
	return (s1);
}

char	*ft_strjoin(char *s1, char *s2) //сделать free первой и второй строчки
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

//char	*ft_strnstr(char *big, char *little, int len)
//
//{
//	int	i;
//	int	j;
//
//	i = 0;
//	if (!*little && !*big)
//		return ((char *)(big + ft_strlen(big)));
//	if (!*little && *big)
//		return ((char *)big);
//	while (i < len && big[i])
//	{
//		j = 0;
//		while (big[i + j] == little[j] && i + j < len)
//		{
//			j++;
//			if (little[j] == '\0')
//				return ((char *)&big[i]);
//		}
//		i++;
//	}
//	return (NULL);
//}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	find_spec_char(char *str) //ищет не цифрово-алфавитный символ
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])))
		i++;
	return (i);
}

char	*ft_strset(int n)
{
	char	*str;

	str = malloc(n + 1);
	if (!str)
		return (NULL);
	while (n-- >= 0)
		str[n] = 0;
	return (str);
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

void big_str_print(char **big_str)
{
	char **tmp;

//	tmp = big_str;
	if (!big_str)
	{
		printf("no big_str\n");
		return ;
	}
	while (*big_str)
		printf("%s\n", *big_str++);
}
void pipe_print(int **pipe_array)
{
	int	i = 0;

	printf("\t--->pipe_array<---\n");
	while (pipe_array[i])
	{
		printf("\t[%d\t", pipe_array[i][0]);
		printf("%d]\n", pipe_array[i][1]);
		i++;
	}
	printf("\n\n");
}
//
//int	ft_strcmp(char *str1, char *str2)
//{
//	int	i;
//
//	i = 0;
//	while (str1[i])
//	{
//		if (str1[i] != str2[i] || !str1[i] || !str2[i])
//			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
//		i++;
//	}
//	return (0);
//}

int	ft_strcmp(char *s1, char *s2) //сравнивает строки
{
	if (!s1 || !s2)
		return (-1);
	while (*s1 == *s2 && *s1++ && *s2++)
		;
	return (*s1 - *s2);
}

int	ft_strncmp(char *str_1, char *str_2, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (str_1[i] != str_2[i])
			return (-1);
		i++;
	}
	return (0);
}

int	ft_putstr_fd(char *s, int fd)
{
	if (s)
		return (write(fd, s, ft_strlen(s)));
	return (0);
}

int ft_perror(char *str)
{
	perror(str);
	return (0);
}
