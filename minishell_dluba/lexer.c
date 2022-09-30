#include "minishell.h"

char *quote_str_trim(char *bash_str, char *sym_arr)
{
	int		len;
	int		i;
	char	*trimmed_str;

	len = ft_strchr(bash_str, sym_arr);
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
	t_list	*temp;
	t_list	**lst;
	char	*str;
	char	*isspecial_arr =  ft_strdup("\'\"\t\n\v\f |<>");

	lst = lst_new(0);
	if (!lst || !bash_str)
		return (NULL);
	if (!*bash_str)
		lst_push_back(lst, lst_elem_new("\0", WORD));
	while (*bash_str)
	{
		if (*bash_str == '\'')
		{
			++bash_str;
			if (ft_strchr(bash_str, "\'") == ft_strlen(bash_str))
				exit(printf("error: no second single quote"));
			str = quote_str_trim(bash_str, "\'");
			lst_push_back(lst, lst_elem_new(str, FIELD));
			bash_str += ft_strchr(bash_str, "\'") + 1;
		}
		else if (*bash_str == '\"')
		{
			++bash_str;
			if (ft_strchr(bash_str, "\"") == ft_strlen(bash_str))
				exit(printf("error: no second double quote"));
			str = quote_str_trim(bash_str, "\"");
			lst_push_back(lst, lst_elem_new(str, EXP_FIELD));
			bash_str += ft_strchr(bash_str, "\"") + 1;
		}
		else if (!ft_strncmp(bash_str, "<<", 2))
		{
			bash_str += 2;
			lst_push_back(lst, lst_elem_new(NULL, REDIR_HEREDOC));
		}
		else if (!ft_strncmp(bash_str, ">>", 2))
		{
			bash_str += 2;
			lst_push_back(lst, lst_elem_new(NULL, REDIR_APPEND));
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
		else if (*bash_str == '|')
		{
			++bash_str;
			lst_push_back(lst, lst_elem_new(NULL, PIPE));
		}
		else if (ft_isspace(*bash_str))
		{
			while (ft_isspace(*bash_str))
				++bash_str;
		}
		else
		{
			str = quote_str_trim(bash_str, isspecial_arr);
			if (!str)
				return (NULL);
			lst_push_back(lst, lst_elem_new(str, WORD));
			bash_str += ft_strchr(bash_str, isspecial_arr);
			
		}
	}
	free(isspecial_arr);
	dollar_parser(lst, vars);
	return (lst);
}
