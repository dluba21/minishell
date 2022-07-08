#include "minishell.h"

int ft_readline(void) //ридайн применить и добавить в истории и проверить на нулл ридлайн
{
	
	return (0);
}



char	*ft_strdup(char *str)
{
	char	*ret_str;
	char	*temp;

	ret_str = (char *)(malloc(ft_strlen(str) + 1));
	if (!ret_str)
		return (NULL);
	temp = ret_str;
	while (*str)
		*temp++ = *str++;
	*temp = 0;
	return (ret_str);
}

int ft_isspace(char c)
{
	if (c >= 9 && c <= 13 || c == 32)
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2) //сравнивает строки
{
	if (!s1 || !s2)
		return (-1);
	while (*s1 == *s2 && *s1++ && *s2++)
		;
	return (*s1 - *s2);
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


//int	ft_strcmp_n(char *s1, char *s2, int n) //сравнивает строки на n символов вперед вперед
////я каждый раз проверяю после его вызова, есть ли конец строки после символа, мб вывести -1, если конец строки?
////и еще мб передвигать указатель, если и правда нашло символы
//{
//	int	i;
//
//	if (!s1 || !s2 || n < 0)
//		return (-1);
//	i = 0;
//	while (i < n)
//	{
//		if (!s1[i] || !s2[i] || s1[i] == s2[i])
//			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
//		i++;
//	}
//	return (0);
//}
//char *
//	  readline (const char *prompt);



//int pipe_len_and_check(char *bash_str) //чекает длину пайпов и синтакис его (а вообще переписать, так как говно)
//{ //лучше сначала внести токены в список и потом уже проверять синтаксис
//	int		i;
//	int		n_pipes;
//	int		isspace_f;
//
//	i = 0;
//	isspace_f = 0;
////	temp = bash_str
//	while (*bash_str)
//	{
//		if (ft_isspace(*bash_str)) //чекаю есть ли пробелы вообще, важно для синтаксиса
//			isspace_f = 1;
//		else if (*bash_str == "|" && !ft_strcmp_n(bash_str, "||", 2) \
//			&& *(bash_str + 1)); //последнее если aboba |
//		{
//			bash_str += 2;
//			isspace_f = 0;
//			n_pipes++;
//			if (!ft_isspace(*(bash_str + 2))) //проверка на синтаксис, есть ли пробел после слова
//				return (-1); //выдать в верхней функции ошибку и написать
//		}
//		else
//			isspace_f = 0;
//		bash_str++;
//	}
//}



//int	bash_args_len(char **argv) //считает количество элементов в списке токенов
//{
//
//}

int ft_strchr(char *str, char *c) //длина пути до нужного символа (если пустая строка или не маллок то -1)
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

char *quote_str_trim(char *bash_str, char *sym_arr) //если подавать char **bash_str, то можно сократить код и будет двигаться указатель срапзу по обрезании
{
	int		len;
	int		i;
	char	*trimmed_str;
	char	*temp; //так как strchr выдает сегу, если не маллочить статическую строку
	temp = ft_strdup(sym_arr);
	len = ft_strchr(bash_str, temp);
	printf("len = %d\n", len);
	free(temp);
//	if (len == -1) //nado li voobshe? esli net iz etogo spiska znachit eto konec stroki, chto normalno
//		return (NULL);
	trimmed_str = (char *)(malloc(len + 1));
	if (!trimmed_str)
		return (NULL);
	i = 0;
	while (i < len)
		trimmed_str[i++] = *bash_str++;
	trimmed_str[i] = 0;
	return (trimmed_str);
}

t_list **bash_args_first_lst_init(char *bash_str)
{
	t_list	*temp; //стереть
	t_list	**lst;
	char	*str;
	char	isspecial_arr[7] = "\'\"\t\n\v\f ";
//	{'\'', '\"', '\t', '\n', '\v', '\f', ' '}; //там слэш ноль должен добавить?

	lst = lst_new(0);
	if (!lst || !bash_str)
		return (NULL);
	while (*bash_str)
	{
//		printf("cmp = %d\n", ft_strcmp_n(bash_str, ">>", 2));
		if (*bash_str == '\'')
		{
			if (!*(++bash_str)) //дальше конец строки и ошибка значит
				exit (printf("error: no second double quote\n")); //не иксит а надо вывести ошибку!!
			str = quote_str_trim(++bash_str, "\'"); //!!вот бля хуй знает, ведь может быть aboba"aboba'aboba, то есть обе кавчки надо учитывать
			if (!str)
				exit (printf("error: no second double quote\n")); //не нашел вторую кавчку, значит ошибку надо выдать и список зафришить созданный уже
			lst_push_back(lst, lst_new_elem(str, FIELD));
			bash_str += ft_strchr(bash_str, "\'") + 1; // +1 чтобы выйти за кавычку
			printf("bash_str = [%s]\n", bash_str);
		}
		else if (*bash_str == '\"') //двойная кавычка
		{
			if (!*(++bash_str)) //++ проехать кавычку и чекнуть конец строки ли следующий
				exit (printf("error: no second single quote\n"));
			str = quote_str_trim(bash_str, "\"");
			if (!str)
				exit (printf("error: no second single quote\n")); //не нашел вторую кавчку, значит ошибку надо выдать и список зафришить созданный уже
			lst_push_back(lst, lst_new_elem(str, EXP_FIELD));
			bash_str += ft_strchr(bash_str, "\"") + 1; //nado li +1??
		}
		else if (!ft_strcmp_n(bash_str, "<<", 2))
		{
			bash_str += 2;
			lst_push_back(lst, lst_new_elem(NULL, REDIR_HEREDOC)); //типа потом уже добавлю delim при парсинге уже
		}
		else if (!ft_strcmp_n(bash_str, ">>", 2))
		{
			bash_str += 2;
//			if (!*bash_str) //nahuy ne nado pohodu
//				return (NULL);
			lst_push_back(lst, lst_new_elem(NULL, REDIR_APPEND)); //типа потом уже добавлю delim при парсинге уже
		}
		else if (*bash_str == '<')
		{
			++bash_str;
			lst_push_back(lst, lst_new_elem(NULL, REDIR_IN));
		}
		else if (*bash_str == '>')
		{
			if (!*(++bash_str))
				return (NULL);
			lst_push_back(lst, lst_new_elem(NULL, REDIR_OUT));
		}
		else if (!ft_strcmp_n(bash_str, "||", 2))
		{
			bash_str += 2;
			lst_push_back(lst, lst_new_elem(NULL, PIPE));
		}
		else if (ft_isspace(*bash_str))
		{
			while (ft_isspace(*bash_str))
				bash_str++;
			lst_push_back(lst, lst_new_elem(NULL, SPACE));
		}
		else
		{
			str = quote_str_trim(bash_str, isspecial_arr);
			if (!str)
				return (NULL);
			lst_push_back(lst, lst_new_elem(str, WORD));
			bash_str += ft_strchr(bash_str, isspecial_arr);
			
		}
	}
	printf("\n\n\n\nresult:\n");
	return (lst);
}

//("aboba 12456 ");

//if (!*(++bash_str))) //дальше конец строки и ошибка значит
//	return (NULL);
//str = quote_str_trim(++bash_str, '\'');
//if (!str)
//	return (NULL); //не нашел вторую кавчку, значит ошибку надо выдать и список зафришить созданный уже
//lst_push_back(lst, lst_new_elem(str, FIELD));
//*bash_str += ft_strchr(bash_str, '\'') + 1; // +1 чтобы выйти за кавычку
//}




//после here_doc может идти word exp_field или field, это можно уже при парсинге чекатб




//надо будет немного переписать так как
//minishell % echo avabab"asvasv" (теперь работает)
//avababasvasv
//если второй кавычки нет чтобы обрабатывало надо

//exit (printf("error: no second once single quote\n")); //не иксит а надо вывести ошибку!!
//пустуж строку обработаьь ""
