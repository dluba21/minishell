/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 01:57:47 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/10/01 01:58:09 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_vars *vars, t_cmd *cmd)
{
	int		i;
	int		len_args;
	int		slash_n_f;

	(void)vars;
	i = 1;
	slash_n_f = 1;
	len_args = lst_len(cmd->args_lst);
	if (cmd->args_array[i] && !ft_strcmp("-n", cmd->args_array[i]))
	{
		slash_n_f = 0;
		++i;
	}
	while (i < len_args - 1)
	{
		ft_putstr_fd(cmd->args_array[i++], cmd->out_fd);
		ft_putstr_fd(" ", cmd->out_fd);
	}
	ft_putstr_fd(cmd->args_array[i], cmd->out_fd);
	if (slash_n_f)
		ft_putstr_fd("\n", cmd->out_fd);
	return (0);
}
