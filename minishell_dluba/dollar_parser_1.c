#include "minishell.h"

void	expand_dollar_var(char **str, char **ret_str, t_vars *vars)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = find_spec_char(*str);
	if (i == 0)
	{
		*ret_str = ft_strjoin(*ret_str, ft_strdup("$"));
		*str = *str + 1;
		return ;
	}
	tmp = find_env_var(ft_substr(*str, 0, i), vars->envp);
	*str += i;
	if (!tmp)
		return ;
	*ret_str = ft_strjoin(*ret_str, tmp);
}

void	not_dollar_part(char **str, char **ret_str)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strchr(*str, "$");
	if (end != 0)
	{
		*ret_str = ft_strjoin(*ret_str, ft_substr(*str, start, end));
		*str += end;
	}
}

void	dollar_expansion_2(char **str, t_vars *vars, char **ret_str)
{
	if (!(*(++(*str))))
	{
		*ret_str = ft_strjoin(*ret_str, ft_strdup("$"));
		return ;
	}
	else if (**str == '?')
	{
		*ret_str = ft_strjoin(*ret_str, ft_itoa(vars->exit_status));
		(*str)++;
	}
	else if (**str == '$')
	{
		*ret_str = ft_strjoin(*ret_str, vars->term_pid);
		(*str)++;
	}
	else if (**str == '{')
	{
		expand_dollar_var_in_brace(str, ret_str, vars);
		not_dollar_part(str, ret_str);
	}
	else
	{
		expand_dollar_var(str, ret_str, vars);
		not_dollar_part(str, ret_str);
	}
}

char	*dollar_expansion(char *str, t_vars *vars)
{
	char	*tmp;
	char	*ret_str;

	if (!str || (ft_strchr(str, "$") == ft_strlen(str)))
		return (str);
	tmp = str;
	ret_str = ft_strdup("");
	not_dollar_part(&str, &ret_str);
	while (*str)
		dollar_expansion_2(&str, vars, &ret_str);
	free(tmp);
	return (ret_str);
}

int	dollar_parser(t_list **lst, t_vars *vars)
{
	t_list	*head;

	if (!lst || !(*lst))
		return (-1);
	head = *lst;
	while (head)
	{
		if (head->key == EXP_FIELD || head->key == WORD)
			head->val = dollar_expansion(head->val, vars);
		if (head->key == EXP_FIELD || head->key == WORD || head->key == FIELD)
			head->key = WORD;
		head = head->next;
	}
	return (0);
}
