#include "minishell.h"

int **open_pipes(int n)
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
			out_fd =  open(head->val, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (head->next)
			close(out_fd);
		head = head->next;
	}
	return (out_fd);
}

int	change_fd(int in_fd, int out_fd, int **pipe_array, int i, int n)
{
	if (i != 0 && in_fd == 0)
		in_fd = pipe_array[i - 1][0];
	if (i != n - 1 && out_fd == 1)
		out_fd = pipe_array[i][1];
	if (dup2(in_fd, 0) == -1)
		return (ft_perror("dup2") - 1);
	if (dup2(out_fd, 1) == -1)
		return (ft_perror("dup2") - 1);
	return (0);
}

int	open_files(t_cmd *cmd, int **pipe_array, int i, int n)
{
	int	in_fd;
	int	out_fd;

	cmd->in_fd = open_files_in(cmd->files_in);
	cmd->out_fd = open_files_out(cmd->files_out);
	change_fd(cmd->in_fd, cmd->out_fd, pipe_array, i, n);
	delete_heredocs(cmd->files_in);
	return (0);
}
