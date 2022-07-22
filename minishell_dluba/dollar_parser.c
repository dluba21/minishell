#include "minishell.h"

//char	*

//мне надо заносить всю строку до доллара сразу и сдвигать по-любому строку, потихонбку строку слева
void	dollar_expansion(t_list *head) //free старую строку
{
	char	*str;
	char	*tmp;
	char	*ret_str;
	int		start;
	int		end;

	str = (char *)head->val;
	if (!str || (ft_strchr(str, "$") == ft_strlen(str))) // дальше значит есть доллар и строка не равна нулю
		return ;
	start = 0;
	tmp = str; //free в конце
	ret_str = ft_strdup(""); //нет доллара или ничего после доллара, дальше ? $ или переменная или кавычки
	while (*str)
	{
		end = ft_strchr(str, "$");
		if (*(++str))  //доллар в конце строки
		{
			ret_str = ft_strjoin(ret_str, str + end); //доллар в конце поэтому заношу как символ
			break ;
		}
		else if (str[i] == '?')
		{
			ret_str = ft_strjoin(ret_str, "{status_terminal}"); //статус терминала дописать потом
			i++;
		}
		else if (str[i] == '$')
		{
			ret_str = ft_strjoin(ret_str, "{status_last_cmd}"); //статус дописать потом
			i++;
		}
//		else if (str[i + 1] == '{') //на кавычку потом обработка еще если париться
		else
		{
			ret_str = ft_strjoin(ret_str, ft_substr()str + start + ft_strchr(str + end, "$")); //
		}
	}
	str = ret_str;
	free(tmp);
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
}
