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
//typedef struct s_list
//{
//	void			*val;
////	void			*key;
//	int				key;
//	struct s_list	*next;
//	struct s_list	*prev;
//}					t_list;
//
//
//int ft_strlen(char *str)
//{
//	int	i;
//
//	i = 0;
//	if (!str)
//		return (-1);
//	while (str[i])
//		i++;
//	return (i);
//}
//
//char	*ft_strdup(char *str)
//{
//	char	*ret_str;
//	char	*temp;
//
//	ret_str = (char *)(malloc(ft_strlen(str) + 1));
//	if (!ret_str)
//		return (NULL);
//	temp = ret_str;
//	while (*str)
//		*temp++ = *str++;
//	*temp = 0;
//	return (ret_str);
//}
//
//
//int ft_strchr(char *str, char *c) //длина пути до нужного символа (если пустая строка или не маллок то -1)
//{//сделать по не char c, а массив символов
////	char	*temp;
//	int		i;
//	int		j;
//
//	i = 0;
//	while (str[i])
//	{
//		j = 0;
//		while (c[j])
//		{
//			if (str[i] == c[j++])
//				return (i);
//		}
//		i++;
//	}
//	return (i); //это исправитьб вдруг нет символов
//	//хз как реализовать через индексы а не укказатели, так как в оригинале при пустой строке и поиске не конца строки выдает NULL
//	//вот начал возвращать i, такое себе
//}
//
//
//
////char	*ft_strchr(char *str, int sym)
////{
////	int	i;
////
////	i = 0;
////	while (str[i])
////	{
////		if (str[i] == (unsigned char)sym)
////			return ((char *)&str[i]);
////		i++;
////	}
////	if (sym == '\0')
////		return ((char *)&str[i]);
////	return (NULL);
////}
////
////
////static char	*blank_kostyl(void)
////{
////	char	*s1;
////
////	s1 = malloc(sizeof(char));
////	if (!s1)
////		return (NULL);
////	s1[0] = '\0';
////	return (s1);
////}
////
////char	*ft_substr(char *s, unsigned int start, size_t len)
////{
////	char	*s1;
////	size_t	i;
////
////	i = 0;
////	if (!s)
////		return (NULL);
////	if (start >= ft_strlen(s))
////		return (blank_kostyl());
////	if (start + len > ft_strlen(s))
////		len = ft_strlen(s) - start;
////	s1 = (char *)malloc(len + 1);
////	if (!s1)
////		return (NULL);
////	if (start < ft_strlen(s) || (len + start) <= ft_strlen(s))
////	{
////		while (i < len)
////			s1[i++] = s[start++];
////	}
////	s1[i] = '\0';
////	return (s1);
////}
////
////char	*ft_strtrim(char *s1, char *set)
////{
////	size_t	i;
////	size_t	j;
////
////	if (!s1 || !set)
////		return (NULL);
////	i = 0;
////	j = ft_strlen(s1);
////	while (ft_strchr(set, s1[i]) && s1[i])
////		i++;
////	while (ft_strchr(set, s1[j]) && j)
////	{
////		j--;
////		if (i > j)
////			return (ft_strdup(""));
////	}
////	return (ft_substr(s1, i, j - i + 1));
////}
//
//
////char *quote_str_trim(char *bash_str, char *sym_arr) //если подавать char **bash_str, то можно сократить код и будет двигаться указатель срапзу по обрезании
////{
////	int		len;
////	int		i;
////	char	*trimmed_str;
////	char	*temp; //так как strchr выдает сегу, если не маллочить статическую строку
////	temp = ft_strdup(sym_arr);
////	len = ft_strchr(bash_str, temp);
//////	printf("len = %d\n", len);
////	free(temp);
//////	if (len == -1) //nado li voobshe? esli net iz etogo spiska znachit eto konec stroki, chto normalno
////	//net, nado, tak kak eto znachit chto vtoroy kavichki net
//////		return (NULL);
//////	printf("len(strchr) = %d\n", len);
////	trimmed_str = (char *)(malloc(len + 1));
////	if (!trimmed_str)
////		return (NULL);
////	i = 0;
////	while (i < len)
////		trimmed_str[i++] = *bash_str++;
////	trimmed_str[i] = 0;
////	return (trimmed_str);
////}
//int main()
//{
//	char *str = ft_strdup("123$45");
//	char	isspecial_arr[10] = "\'\"\t\n\v\f |<>";
////	char *str_2 = quote_str_trim(str, isspecial_arr);
////	printf("%s\n", str_2);
//	
//	
//	t_list **lst = NULL;
//	
////	if (!lst || !)
////		printf("ok\n");
//	printf("s = [%c]\n", str[ft_strchr(str, "$")]);
////	int i = 0;
////
////	while (i < 10)
////	{
////		printf("aboba\n");
////		i++;
////	}
////	char	isspecial_arr[7] = {'\'', '\"', '\t', '\n', '\v', '\f', ' '}; //там слэш ноль должен добавить?
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
////	int i = 0100000;
////	printf("%d", i);
//}
