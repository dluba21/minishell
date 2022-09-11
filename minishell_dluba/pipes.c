#include "minishell.h"

//если кличество пайпов четное количество (команд  на один меньше, то по нулям в первом пайпе)

int **open_pipes(int len) //создаю массив из пайпов, пайпов меньше на один чем команд как максимум
{
	int		**pipe_array;
	int		pipe_fd[2];
	int		i;

	
	if (len == 0) //!убрать(11.09)!!! нет пайпов (вообще сюда не зайдет никогда так как там выходит сверху в условии одной команды)
		return (NULL);
	pipe_array = (int **)malloc(sizeof(int *) * (len + 1)); //leaks
	i = 0;
	while (i < len)
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


int	open_files(t_cmd *cmd, int *in_fd, int *out_fd, int **pipe_array, int i, int n, int *heredoc_f) //открывает файлы и делает dup2 с ними или с пайпами
{
	t_list	*head;
//	int		heredoc_f;

	*in_fd = 0; //закроется ли STDIN и STDOUT?
	*out_fd = 1;
	*heredoc_f = 0; //надо ли инициализировать?
	head = *(cmd->files_in); //все файлы с разными токенами на ввод и ивывод следует переделать название на cmd->files

//	if (i != 0)
//		sleep(5);
	while (head)
	{
//		close(*in_fd);
//		close(*out_fd);
		if (head->key == REDIR_IN) //если встретил редирин то флаг хердок опустить и присво
		{
			*in_fd = open(head->val, O_RDONLY, 0644);
			*heredoc_f = 0; //мб что есть heredoc, но он находится до другого ввода файла. То есть флаг показывает, надо ли считывать с heredoc
		}
		else if (head->key == REDIR_OUT)
			*out_fd = open(head->val, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (head->key == REDIR_APPEND)
			*out_fd = open(head->val, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (head->key == REDIR_HEREDOC)
			*heredoc_f = 1;
		if (*in_fd == -1)
			return (ft_perror("error") - 1);
		head = head->next;
	}
	
	//в конце цикла есть фдшник точно (если редирект, то он остается, если хердок, то он остается, а мб ничего не поменялось)

//	printf("ok(%d)\n", getpid());
	

//	printf("pipe[%d][0] = %d\n", i, pipe_array[i][0]);
//	sleep(1000);
	if (i != 0 && *in_fd == 0 && !(*heredoc_f)) //если не первая команда, если фдшник_ин не менялся и если нет флага хердок, значит ввода из другого места нет и там стоит спереди пайп
		*in_fd = pipe_array[i - 1][0];
//	write(2, "ok!\n", 4);
//	sleep(1000);


	if (i != n - 1 && *out_fd == 1)  //если не последняя команда, если фдшник_аут не менялся
		*out_fd = pipe_array[i][1];
	
	
	heredoc_parser(cmd->files_in, in_fd, *heredoc_f); //не забыть анлинк в конце команды, там если heredoc_f == 1, то in_fd заменяется
//	if (*heredoc_f)
//	{
//		*in_fd = open("heredoc_file", O_RDWR, 0644);
//		ft_perror("write_error");
//		if (write(*in_fd, "abobek\n", 7) == -1)
//			printf("here_doc error: can't write");
//	
//		printf("str = {%s}\n", get_next_line(*in_fd));
//	}
	printf("proc[%d]\t\tin_fd = %d, out_fd = %d\n", i, *in_fd, *out_fd);
//	write(2, "ok!\n", 4);
//		printf("in_fd = %d, i = %d, *heredoc = %d\n", *in_fd, i, *heredoc_f);
	if (dup2(*in_fd, 0) == -1)
		return (ft_perror("error") - 1);
	if (dup2(*out_fd, 1) == -1)
		return (ft_perror("error") - 1);
	if (n > 1)
		close_all_pipes(pipe_array); //закрыл все лишние пайпы
//	sleep(1000);
//	sleep(1000);
//к этому моменту открыли файлы и заменили все фдшники
	return (0);
}
