#include "minishell.h"

//если кличество пайпов четное количество (команд  на один меньше, то по нулям в первом пайпе)

int **open_pipes(int n) //создаю массив из пайпов, пайпов меньше на один чем команд как максимум
{
	int		**pipe_array;
	int		pipe_fd[2];
	int		i;

	
	if (n < 2)
		return (NULL);
	pipe_array = (int **)malloc(sizeof(int *) * n); //leaks
	i = 0;
	while (i < n - 1)
	{
		pipe_array[i] = (int *)malloc(sizeof(int) * 2); //leaks
		pipe(pipe_fd);
//		printf("pipe_fd[0] = %d\tpipe_fd[1] = %d\n", pipe_fd[0], pipe_fd[1]);
		pipe_array[i][0] = pipe_fd[0];
		pipe_array[i++][1] = pipe_fd[1];
//		printf("pipe_array[%d][0] = %d\tpipe_array[%d][1] = %d\n\n", i, pipe_array[i][0], i, pipe_array[i][1]);
	}
	pipe_array[i] = NULL;
	pipe_print(pipe_array);
	return (pipe_array);
}

void	close_all_pipes(int **pipe_array)
{
	int	i;

	i = 0;
	while (pipe_array[i])
	{
		close(pipe_array[i][0]);
		close(pipe_array[i++][1]);
	}
}

int	open_files_in(t_list **files_in) //unlink vseh heredocs!!!!
{
	t_list	*head;

	head = lst_get_last(files_in);
	if (!head)
		return (0);
	if (access(head->val, F_OK | R_OK) == -1)
		exit(ft_perror(head->val) - 1);
	printf("infile = {%s}\n", (char *)head->val);
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

int	change_fd(int in_fd, int out_fd, int **pipe_array, int i, int n) //need structure!!!
{
	if (i != 0 && in_fd == 0)
		in_fd = pipe_array[i - 1][0];
	if (i != n - 1 && out_fd == 1)
		out_fd = pipe_array[i][1];
	printf("proc[%d]\t\tin_fd = %d, out_fd = %d\n", i, in_fd, out_fd);
	if (dup2(in_fd, 0) == -1)
		return (ft_perror("dup2") - 1);
	if (dup2(out_fd, 1) == -1)
		return (ft_perror("dup2") - 1);
	return (0);
}

int	open_files(t_cmd *cmd, int **pipe_array, int i, int n) //открывает файлы и делает dup2 с ними или с пайпами
{
	int	in_fd;
	int	out_fd;

	in_fd = open_files_in(cmd->files_in);
	out_fd = open_files_out(cmd->files_out);
	change_fd(in_fd, out_fd, pipe_array, i, n);
//	printf("proc[%d]\t\tin_fd = %d, out_fd = %d\n", i, in_fd, out_fd);
//	write(2, "ok!\n", 4);
//		printf("in_fd = %d, i = %d, *heredoc = %d\n", *in_fd, i, *heredoc_f);
	delete_heredocs(cmd->files_in);
	if (pipe_array)
		close_all_pipes(pipe_array); //закрыл все лишние пайпы
//	sleep(1000);
//	sleep(1000);
//к этому моменту открыли файлы и заменили все фдшники
	return (0);
}
