#include "minishell.h"



void	env_var_trimmer(char *env_elem, char **buffer) // записывает в буфер все до '='
{
	char	*tmp;

	tmp = *buffer;
	while (*env_elem && *env_elem != '=')
		*tmp++ = *env_elem++;
	if (!*env_elem)
		printf("no '=' in envp\n"); //удалить, такое не бывает, наверное
	*tmp = 0;
}

char	*env_key_trimmer(char *env_elem)
{
	char	*key;
	char	*tmp;
	
	while (*env_elem && *env_elem != '=')
		env_elem++;
	env_elem++; // перешел за '='
	key =  (char *)malloc(ft_strlen(env_elem) + 1);
	if (!key)
		return (NULL);
	tmp = key;
	while (*env_elem)
		*tmp++ = *env_elem++;
	*tmp = 0;
	return (key);
}

char	*find_env_var(char *str, char **env) //ищет среди переменных окружения нужное или возвращает пустую строку если не нашло
{
	char	*buffer;
	char	*dollar_str;
	int		i;

	if (!env)
	{
		printf("error: no envp in dollar parser!\n");
		return (NULL);
	}
	dollar_str = NULL;
	buffer = ft_strset(100); // создает буфер
	while (*env)
	{
		env_var_trimmer(*env, &buffer);
		if (!ft_strcmp(str, buffer)) //если строки равны
		{
			dollar_str = env_key_trimmer(*env);
			break ;
		}
		env++;
	}
	free(buffer);
	free(str);
	if (!dollar_str) //если в итоге не нашло такую переменную
		return (NULL);
	return (dollar_str);
}

void    expand_dollar_var_in_brace(char **str, char **ret_str, t_vars *vars)
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
	printf("ret_str = [%s]\n", ret_str);
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
		head = head->next;
	}
	return (0);
}
