/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 01:50:12 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/10/01 01:58:09 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**open_pipes(int n)
{
	int		**pipe_array;
	int		pipe_fd[2];
	int		i;

	if (n < 2)
		return (NULL);
	pipe_array = (int **)malloc(sizeof(int *) * n);
	i = 0;
	while (i < n - 1)
	{
		pipe_array[i] = (int *)malloc(sizeof(int) * 2);
		pipe(pipe_fd);
		pipe_array[i][0] = pipe_fd[0];
		pipe_array[i++][1] = pipe_fd[1];
	}
	pipe_array[i] = NULL;
	return (pipe_array);
}

void	close_all_pipes(int **pipe_array)
{
	int	i;

	i = -1;
	while (pipe_array[++i])
	{
		close(pipe_array[i][0]);
		close(pipe_array[i][1]);
		free(pipe_array[i]);
	}
	free(pipe_array);
	pipe_array = NULL;
}
