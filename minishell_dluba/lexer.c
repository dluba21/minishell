#include "minishell.h"




char *quote_str_trim(char *bash_str, char *sym_arr) //если подавать char **bash_str, то можно сократить код и будет двигаться указатель срапзу по обрезании
{
	int		len;
	int		i;
	char	*trimmed_str;

	len = ft_strchr(bash_str, sym_arr);
//	printf("len = %d\n", len);
//	if (len == -1) //nado li voobshe? esli net iz etogo spiska znachit eto konec stroki, chto normalno
	//net, nado, tak kak eto znachit chto vtoroy kavichki net
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

t_list **bash_args_lst_lexer(char *bash_str, t_vars *vars)
{
	t_list	*temp; //стереть
	t_list	**lst;
	char	*str;
	char	*isspecial_arr =  ft_strdup("\'\"\t\n\v\f |<>");

//	{'\'', '\"', '\t', '\n', '\v', '\f', ' '}; //там слэш ноль должен добавить?

	lst = lst_new(0);
	if (!lst || !bash_str)
		return (NULL);
//	printf("{%d}\n", *(bash_str + 13));
	if (!*bash_str)
		lst_push_back(lst, lst_elem_new("\0", WORD));
	while (*bash_str)
	{
//		printf("cmp = %d\n", ft_strcmp_n(bash_str, ">>", 2));
		if (*bash_str == '\'')
		{
			++bash_str;
			if (ft_strchr(bash_str, "\'") == ft_strlen(bash_str))
				exit(printf("error: no second single quote")); //не нашел вторую кавчку, значит ошибку надо выдать и список зафришить созданный уже
			str = quote_str_trim(bash_str, "\'");
			lst_push_back(lst, lst_elem_new(str, FIELD));
			bash_str += ft_strchr(bash_str, "\'") + 1; // +1 чтобы выйти за кавычку
		}
		else if (*bash_str == '\"') //двойная кавычка
		{
			++bash_str;
			if (ft_strchr(bash_str, "\"") == ft_strlen(bash_str))
				exit(printf("error: no second double quote")); //не нашел вторую кавчку, значит ошибку надо выдать и список зафришить созданный уже
			str = quote_str_trim(bash_str, "\"");
			lst_push_back(lst, lst_elem_new(str, EXP_FIELD));
			bash_str += ft_strchr(bash_str, "\"") + 1; //nado li +1??
		}
		else if (!ft_strncmp(bash_str, "<<", 2))
		{
			bash_str += 2;
			lst_push_back(lst, lst_elem_new(NULL, REDIR_HEREDOC)); //типа потом уже добавлю delim при парсинге уже
		}
		else if (!ft_strncmp(bash_str, ">>", 2))
		{
			bash_str += 2;
//			if (!*bash_str) //nahuy ne nado pohodu
//				return (NULL);
			lst_push_back(lst, lst_elem_new(NULL, REDIR_APPEND)); //типа потом уже добавлю delim при парсинге уже
		}
		else if (*bash_str == '<')
		{
			++bash_str;
			lst_push_back(lst, lst_elem_new(NULL, REDIR_IN));
		}
		else if (*bash_str == '>')
		{
			++bash_str;
			lst_push_back(lst, lst_elem_new(NULL, REDIR_OUT));
		}
//		else if (!ft_strcmp_n(bash_str, "||", 2)) //для бонуса если что
//		{
//			bash_str += 2;
//			lst_push_back(lst, lst_elem_new(NULL, OR));
//		}
		else if (*bash_str == '|')
		{
			++bash_str;
			lst_push_back(lst, lst_elem_new(NULL, PIPE));
		}
		else if (ft_isspace(*bash_str))
		{
			while (ft_isspace(*bash_str))
				++bash_str;
//			lst_push_back(lst, lst_elem_new(NULL, SPACE));
		}
		else
		{
			str = quote_str_trim(bash_str, isspecial_arr);
			if (!str)
				return (NULL);
			lst_push_back(lst, lst_elem_new(str, WORD));
			bash_str += ft_strchr(bash_str, isspecial_arr);
//			printf("char = %c\n", *bash_str);
			
		}
	}
	printf("\n\n\n\nresult:\n");
	free(isspecial_arr); //также фришить при ошибках надо
	dollar_parser(lst, vars);
	return (lst);
}

//("aboba 12456 ");

//if (!*(++bash_str))) //дальше конец строки и ошибка значит
//	return (NULL);
//str = quote_str_trim(++bash_str, '\'');
//if (!str)
//	return (NULL); //не нашел вторую кавчку, значит ошибку надо выдать и список зафришить созданный уже
//lst_push_back(lst, lst_elem_new(str, FIELD));
//*bash_str += ft_strchr(bash_str, '\'') + 1; // +1 чтобы выйти за кавычку
//}




//после here_doc может идти word exp_field или field, это можно уже при парсинге чекатб




//надо будет немного переписать так как
//minishell % echo avabab"asvasv" (теперь работает)
//avababasvasv
//если второй кавычки нет чтобы обрабатывало надо

//exit (printf("error: no second once single quote\n")); //не иксит а надо вывести ошибку!!
//пустуж строку обработаьь "" - есть


//echo "huy" > lol kek
//2|cat не обрабатывает

//<<ls|cat>aboba
