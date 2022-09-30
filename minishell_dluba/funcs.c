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

	str = (char *)malloc(n + 1);
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

//int	ft_strcmp_n(const char *str1, const char *str2, size_t n)
//{
//	size_t	i;
//
//	i = 0;
//	while (i < n)
//	{
//		if (str1[i] != str2[i] || !str1[i] || !str2[i])
//			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
//		i++;
//	}
//	return (0);
//}

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


int		ft_putendl_fd(char *s, int fd)
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

int ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_strcmp_n(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i] || !str1[i] || !str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}



int	ft_strchr(char *str, char *c) //длина пути до нужного символа (если пустая строка или не маллок то -1)
{//сделать по не char c, а массив символов
//	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (c[j])
		{
			if (str[i] == c[j++])
				return (i);
		}
		i++;
	}
	return (i); //это исправитьб вдруг нет символов
	//хз как реализовать через индексы а не укказатели, так как в оригинале при пустой строке и поиске не конца строки выдает NULL
	//вот начал возвращать i, такое себе
}





static int	sign_checker(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

static int	long_checker(const char *str, int i, int sign)
{
	int			len;
	long int	mod;

	mod = 0;
	len = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (sign == -1 && ((mod == 922337203685477580 && \
		(str[i] - '0' >= 8)) || len >= 19))
			return (0);
		if (sign == 1 && ((mod == 922337203685477580 \
		&& (str[i] - '0' >= 7)) || len >= 19))
			return (-1);
		mod = mod * 10 + str[i++] - '0';
		len++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	sign;
	int	mod;

	i = 0;
	j = 0;
	mod = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (j > 0)
			return (0);
		sign = sign_checker(str[i++]);
		j++;
	}
	if (long_checker(str, i, sign) < 1)
		return (long_checker(str, i, sign));
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		mod = mod * 10 + str[i++] - '0';
	return (mod * sign);
}

