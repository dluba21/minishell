/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parser_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 01:46:48 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/10/01 01:58:09 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	*str += i + 1;
	if (!tmp)
		return ;
	*ret_str = ft_strjoin(*ret_str, tmp);
}
