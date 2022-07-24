#include "minishell.h"

//char	*
//char	*find_env_var(char *str, char **env) //ищет среди переменных окружения нужное или возвращает пустую строку если не нашло
//{
//
//
//	free(str);
//}

void	expand_dollar_var(char **str, char **ret_str)
{
	int	i;

	i = find_spec_char(*str);
	if (i == 0) //например пробел после доллара сразу
	{
		*ret_str = ft_strjoin(*ret_str, ft_strdup("$"));
		(*str)++;
		return ;
	}
//	*ret_str = ft_strjoin(*ret_str, find_env_var(char *str, char **env)); //нашел переменную или не нашел
	*ret_str = ft_strjoin(*ret_str, ft_strdup("{env_var}"));
	*str += i; //мб доллар следующий найдет
}

void	not_dollar_part(char **str, char **ret_str) //сюда подалась строка с частью до доллара - обычное слово, надо все занести как слово до доллара первого
{
	int	start;
	int	end;

	start = 0;
	end = ft_strchr(*str, "$");
	if (end != 0) //если не "$" один
	{
		*ret_str = ft_strjoin(*ret_str, ft_substr(*str, start, end - 1)); //все до доллара копируем,надо поменять -1!!!!
		*str += end; //останавлиаемся на первом долларе
	}
	//что делать если сразу доллар?
}


//мне надо заносить всю строку до доллара сразу и сдвигать по-любому строку, потихонбку строку слева
//void	dollar_expansion(t_list *head)
char *dollar_expansion(char *str) //free старую строку
{
//	char	*str;
	char	*tmp;
	char	*ret_str;

//	str = (char *)head->val;
	if (!str || (ft_strchr(str, "$") == ft_strlen(str))) // дальше значит есть доллар и строка не равна нулю и ничего не меняли в строке
		return (str);
//	if (ft_strchr(str, "$") == )
	tmp = str; //free в конце
	ret_str = ft_strdup(""); //нет доллара или ничего после доллара, дальше ? $ или переменная или кавычки
	//первый кусок до раскрытия (инициализция)
	not_dollar_part(&str, &ret_str); //исправить, почему то обрезает одну букву перед долларом!!!!!
	while (*str)
	{
//		end = ft_strchr(str + 1, "$"); // нашел доллар
		if (!(*(++str)))  //доллар в конце строки
		{
			ret_str = ft_strjoin(ret_str, ft_strdup("$")); //доллар в конце поэтому заношу как символ
			break ;
		}
		else if (*str == '?')
		{
			ret_str = ft_strjoin(ret_str, ft_strdup("{status_terminal}")); //статус терминала дописать потом
			str++;
		}
		else if (*str == '$')
		{
			ret_str = ft_strjoin(ret_str, ft_strdup("{status_last_cmd}")); //статус дописать потом
			str++;
		}
//		else if (*str == '{') //на кавычку потом обработка еще если париться
//		else if (*str == ' ') // искать переменую окружения
		else //
		{
			expand_dollar_var(&str, &ret_str); //после этого в ret_str найденная переменная и str сдвинулось сразу до не алфавитно-цифрового символа (мб до доллара сразу)
			not_dollar_part(&str, &ret_str);
		}
		
	}
//	head->""
	printf("ret_str = [%s]\n", ret_str);
	free(tmp);
	return (str);
	
}


int	dollar_parser(t_list **lst)
{
	t_list	*head;

	if (!lst || !(*lst))
		return (printf("dollar_parser error: no lst or elem\n"));
	head = *lst;
	while (head)
	{
		if (head->key == EXP_FIELD || head->key == WORD)
//			dollar_expansion();
		head = head->next;
	}
	return (0);
}
