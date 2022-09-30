/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 01:49:46 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/10/01 01:58:09 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cond_p1(char **bash_str, char **str, t_list **lst)
{
	if (**bash_str == '\'')
	{
		++(*bash_str);
		if (ft_strchr(*bash_str, "\'") == ft_strlen(*bash_str))
			exit(printf("error: no second single quote"));
		*str = quote_str_trim(*bash_str, "\'");
		lst_push_back(lst, lst_elem_new(*str, FIELD));
		*bash_str += ft_strchr(*bash_str, "\'") + 1;
		return (1);
	}
	else if (**bash_str == '\"')
	{
		++(*bash_str);
		if (ft_strchr(*bash_str, "\"") == ft_strlen(*bash_str))
			exit(printf("error: no second double quote"));
		*str = quote_str_trim(*bash_str, "\"");
		lst_push_back(lst, lst_elem_new(str, EXP_FIELD));
		*bash_str += ft_strchr(*bash_str, "\"") + 1;
		return (1);
	}
	return (0);
}

int	cond_p2(char **bash_str, t_list **lst)
{
	if (!ft_strncmp(*bash_str, ">>", 2))
	{
		*bash_str += 2;
		lst_push_back(lst, lst_elem_new(NULL, REDIR_APPEND));
		return (1);
	}
	else if (**bash_str == '>')
	{
		++(*bash_str);
		lst_push_back(lst, lst_elem_new(NULL, REDIR_OUT));
		return (1);
	}
	return (0);
}

int	cond_p3(char **bash_str, t_list **lst)
{
	if (!ft_strncmp(*bash_str, "<<", 2))
	{
		*bash_str += 2;
		lst_push_back(lst, lst_elem_new(NULL, REDIR_HEREDOC));
		return (1);
	}
	else if (**bash_str == '<')
	{
		++(*bash_str);
		lst_push_back(lst, lst_elem_new(NULL, REDIR_IN));
		return (1);
	}
	return (0);
}

int	cond_p4(char **bash_str, t_list **lst)
{
	if (**bash_str == '|')
	{
		++(*bash_str);
		lst_push_back(lst, lst_elem_new(NULL, PIPE));
		return (1);
	}
	else if (ft_isspace(**bash_str))
	{
		while (ft_isspace(**bash_str))
			++(*bash_str);
		return (1);
	}
	return (0);
}

t_list	**bash_args_lst_lexer(char *bash_str, t_vars *vars)
{
	t_list	**lst;
	char	*str;
	char	*isspecial_arr;

	isspecial_arr = ft_strdup("\'\"\t\n\v\f |<>");
	lst = lst_new(0);
	if (!lst || !bash_str)
		return (NULL);
	if (!*bash_str)
		lst_push_back(lst, lst_elem_new("\0", WORD));
	while (*bash_str)
	{
		if (!cond_p1(&bash_str, &str, lst) && !cond_p2(&bash_str, lst) \
				&& !cond_p3(&bash_str, lst) && !cond_p4(&bash_str, lst))
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
