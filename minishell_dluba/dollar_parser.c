#include "minishell.h"



void	expand_dollar_var_in_brace(char **str, char **ret_str, t_vars *vars)
{
	int		i;
    char	*tmp;

	tmp = NULL;
	i = ft_strchr(++(*str), "}");
	if (i == ft_strlen(*str))
		exit(printf("error: no second brace in dollar_parser\n"));
	tmp = find_env_var(ft_substr(*str, 0, i), vars->envp);
	*str += i + 1; //мб доллар следующий найдет
	if (!tmp) //если не нашло переменную то ничего не меняем вроде //
		return ;
	*ret_str = ft_strjoin(*ret_str, tmp);
}

void	expand_dollar_var(char **str, char **ret_str, t_vars *vars)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = find_spec_char(*str);
	if (i == 0) //например пробел после доллара сразу
	{
		*ret_str = ft_strjoin(*ret_str, ft_strdup("$"));
		*str = *str + 1;
		return ;
	}
	//нашел переменную или не нашел
//	printf("dollar_word = {%s}\n", ft_substr(*ret_str, 0, i));
//	char *kek = ft_substr(*str, 0, i);
	tmp = find_env_var(ft_substr(*str, 0, i), vars->envp); //здесь ошибка!!!
	*str += i; //мб доллар следующий найдет
	if (!tmp) //если не нашло переменную то ничего не меняем вроде //
		return ;
	*ret_str = ft_strjoin(*ret_str, tmp);
//	*ret_str = ft_strjoin(*ret_str, ft_strdup("{env_var}"));
	
	
	//ЕСЛИ ПЕРЕМЕННАЯ ЕСТЬ ТО ЗБС, ПРОВЕРИТЬ 80 СТРОЧКУ!!!
	
}

void	not_dollar_part(char **str, char **ret_str) //сюда подалась строка с частью до доллара - обычное слово, надо все занести как слово до доллара первого
{
	int	start;
	int	end;

	start = 0;
	end = ft_strchr(*str, "$");
	if (end != 0) //если не "$" один
	{
		*ret_str = ft_strjoin(*ret_str, ft_substr(*str, start, end)); //все до доллара копируем,надо поменять -1!!!!
		*str += end; //останавлиаемся на первом долларе
	}
	//что делать если сразу доллар?
}


//мне надо заносить всю строку до доллара сразу и сдвигать по-любому строку, потихонбку строку слева
//void	dollar_expansion(t_list *head)
char *dollar_expansion(char *str, t_vars *vars) //free старую строку
{
//	char	*str;
	char	*tmp;
	char	*ret_str;

//	str = (char *)head->val;

	if (!str || (ft_strchr(str, "$") == ft_strlen(str)))	//проверка на отсутсвие доллара
		return (str);
	// дальше значит есть доллар и строка не равна нулю и ничего не меняли в строке
//	if (ft_strchr(str, "$") == )
	tmp = str; //free в конце
	ret_str = ft_strdup(""); //нет доллара или ничего после доллара, дальше ? $ или переменная или кавычки
	//первый кусок до раскрытия (инициализция)
	not_dollar_part(&str, &ret_str);
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
			ret_str = ft_strjoin(ret_str, ft_itoa(vars->exit_status));
			str++;
		}
		else if (*str == '$')
		{
			ret_str = ft_strjoin(ret_str, vars->term_pid); //статус терминала дописать потом
			str++;
		}
		else if (*str == '{') //на кавычку потом обработка еще если париться
		{
			expand_dollar_var_in_brace(&str, &ret_str, vars);
			not_dollar_part(&str, &ret_str);
		}
//		else if (*str == ' ') // искать переменую окружения
		else //
		{
			expand_dollar_var(&str, &ret_str, vars); //после этого в ret_str найденная переменная и str сдвинулось сразу до не алфавитно-цифрового символа (мб до доллара сразу)
			not_dollar_part(&str, &ret_str);
		}
		
	}
//	head->""
//	printf("ret_str = [%s]\n", ret_str);
	free(tmp);
	return (ret_str);
	
}


int	dollar_parser(t_list **lst, t_vars *vars)
{
	t_list	*head;

	if (!lst || !(*lst))
		return (printf("dollar_parser error: no lst or elem\n"));
	head = *lst;
	while (head)
	{
		if (head->key == EXP_FIELD || head->key == WORD)
			head->val = dollar_expansion(head->val, vars);
		if (head->key == EXP_FIELD || head->key == WORD || head->key == FIELD)
			head->key = WORD; //чтобы потом не делать кучу строчек на условия
		head = head->next;
	}
	return (0);
}
