/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 01:50:06 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/10/01 01:58:09 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*cmd_init(void)
{
	t_list	*lst_elem;
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->files_in = lst_new(0);
	cmd->files_out = lst_new(0);
	cmd->files_heredoc = lst_new(0);
	cmd->args_lst = lst_new(0);
	cmd->args_array = NULL;
	cmd->vars = NULL;
	if (!cmd->files_in || !cmd->files_out || \
		!cmd->files_heredoc || !cmd->args_lst)
		return (NULL);
	lst_elem = lst_elem_new(cmd, 0);
	if (!lst_elem)
		return (NULL);
	return (lst_elem);
}
