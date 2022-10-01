/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 01:57:44 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/10/01 01:58:09 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_files_in(t_list **files_in)
{
	t_list	*head;

	head = lst_get_last(files_in);
	if (!head)
		return (0);
	if (access(head->val, F_OK | R_OK) == -1)
		exit(ft_perror(head->val) - 1);
	return (open(head->val, O_RDONLY, 0644));
}

int	open_files_out(t_list **files_out)
{
	t_list	*head;
	int		out_fd;

	if (!files_out || !(*files_out))
		return (1);
	head = *files_out;
	while (head)
	{
		if (head->key == REDIR_OUT)
			out_fd = open(head->val, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (head->key == REDIR_APPEND)
			out_fd = open(head->val, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (head->next)
			close(out_fd);
		head = head->next;
	}
	return (out_fd);
}

int	change_fd(t_vars *vars, t_cmd *cmd, int i)
{
	if (i != 0 && cmd->in_fd == 0)
		cmd->in_fd = vars->pipe_array[i - 1][0];
	if (i != vars->llst_len - 1 && cmd->out_fd == 1)
		cmd->out_fd = vars->pipe_array[i][1];
	if (dup2(cmd->in_fd, 0) == -1)
		return (ft_perror("dup2") - 1);
	if (dup2(cmd->out_fd, 1) == -1)
		return (ft_perror("dup2") - 1);
	return (0);
}

int	open_files(t_vars *vars, t_cmd *cmd, int i)
{
	cmd->in_fd = open_files_in(cmd->files_in);
	cmd->out_fd = open_files_out(cmd->files_out);
	change_fd(vars, cmd, i);
	delete_heredocs(cmd->files_in);
	return (0);
}
