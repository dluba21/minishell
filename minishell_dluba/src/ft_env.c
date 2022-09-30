/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 01:57:50 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/10/01 01:58:09 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_vars *vars, t_cmd *cmd)
{
	t_list	*head;

	if (!vars->envp_lst)
		return (-1);
	head = *vars->envp_lst;
	while (head)
	{
		ft_putendl_fd((char *)head->val, cmd->out_fd);
		head = head->next;
	}
	return (0);
}
