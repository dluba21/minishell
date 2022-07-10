//# include <stdio.h>
//# include <unistd.h>
//# include <stdlib.h>
//# include <signal.h>
//# include <fcntl.h>
//# include <readline/readline.h>
//# include <readline/history.h>
//# include <string.h>
////#include "minishell.h"
//
//
//
//int ft_strchr(char *str, char *c) //длина пути до нужного символа (если пустая строка или не маллок то -1)
//{//сделать по не char c, а массив символов
//	char	*temp;
//	int		i;
//
//	i = 0;
//	while (str[i])
//	{
//		while (*temp)
//		{
//			if (str[i] == *temp++)
//				return (i);
//		}
//		temp = c;
//		i++;
//	}
//	return (-1);
//}
//
//char *quote_str_trim(char *bash_str, char *sym_arr) //если подавать char **bash_str, то можно сократить код и будет двигаться указатель срапзу по обрезании
//{
//	int		len;
//	int		i;
//	char	*trimmed_str;
//	char	*temp; //так как strchr выдает сегу, если не маллочить статическую строку
//	temp = strdup(sym_arr);
//	len = ft_strchr(bash_str, temp);
//	free(temp);
//	if (len == -1)
//		return (NULL);
//	trimmed_str = (char *)(malloc(len + 1));
//	if (!trimmed_str)
//		return (NULL);
//	i = 0;
//	while (i < len)
//		trimmed_str[i++] = *bash_str++;
//	trimmed_str[i] = 0;
//	return (trimmed_str);
//}
//
//
//
////char            *readline(const char *);
//
////int	ft_strcmp_n(char *s1, char *s2, int n) //сравнивает строки на n символов вперед вперед
////{
////	if (!s1 || !s2 || n < 0)
////		return (-1);
////	printf("%c = %d\t%c = %d\n", *s1, *s1, *s2, *s2);
////	while (*s1 == *s2 && *s1++ && *s2++ && n--)
//////	printf("ok");
////	printf("%c\t%c\n", *s1, *s2);
////	return (*s1 - *s2);
////}
//
////void ft_abobus(char **str)
////{
////	*str += 2;
////}
//
//
//char	*ft_strdup(char *str)
//{
//	char	*ret_str;
//	char	*temp;
//
//	ret_str = (char *)(malloc(strlen(str) + 1));
//	if (!ret_str)
//		return (NULL);
//	temp = ret_str;
//	while (*str)
//		*temp++ = *str++;
//	*temp = 0;
//	return (ret_str);
//}
//
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
//
//int main()
//{
//	char	isspecial_arr[7] = {'\'', '\"', '\t', '\n', '\v', '\f', ' '}; //там слэш ноль должен добавить?
////	char s[6] = "abcdef";
////	char *aboba[7];
////	aboba = {"REDIR_APPNED", "cd", "pwd", "export", "unset", "env", "exit"};
////	char s2[6] = "abcdeo";
////	char *str;
////	str = &s[0];
//////	char *
////	printf("%s", aboba[0]);
//////		  readline (const char *prompt);
//////	char *str = readline("./minishell ");
//////	printf("%s", str);
////	int  i = 0;
////	ft_abobus(&str);
////	while (i < 33)
////		printf("%d = {%c}\n", i, i++);
////	printf("%c\n", "/""); //9<= <=13 && 32
////	printf("{%c}\n", *s);
//
////	typeof(array);
////	array[0] = "aboba";
////	printf("%s", array[0]);
////	printf("{%d}\n", isspecial_arr[6]);
////	int i = 0;
////	char *str = ft_strdup("12456 ");
////	int len = ft_strchr(str, isspecial_arr);
////	printf("len = %d\n", len);
////	int n = 2;
////	char *str_2 = ft_strdup("   aboba   < 12456 ");
////	char *str = ft_strdup("<<");
////	printf("%d\n", ft_strcmp_n(str, str_2, n));
////	printf("%d\n", strncmp(str, str_2, n));
////	char *p = strchr(str, '');
////	printf("%s\n", p);
////	str += len;
////	char *str_2 = quote_str_trim(str, isspecial_arr);
////	printf("str = %s\n", str);
////	printf("len = %d\n", len);
////	printf("%s\n", str_2);
////	printf("[%s]\n", str);
////	printf("%d\n", '\"');
////	printf("ok\n");
//}
