#include "minishell.h"

int	root_paths_init(t_vars *vars) //создает массив строк с путями к командам, надо зачиситить от ликов потом, это вызвать в дочернем процессе
//ф!!!дочерний процесс
{
	int	i;

	i = 0;
	while (vars->envp[i])
	{
		if (!ft_strncmp("PATH=", vars->envp[i], 5)) //работает, так как '=' делитель
		{
			vars->root_paths = ft_split(vars->envp[i] + 5, ':');
			if (!vars->root_paths)
				return (0);
			return (-1);
		}
		i++;
	}
	return (printf("error: no paths in env!\n") - 25);
}

char	*compose_cmd_path(t_cmd *cmd_elem, char **root_paths) //создает путь к команде для execve(билтин точно нет уже, отсею выше !!!!ПОСЛЕ ЭТОГО ЗАФРИШИТЬ ROOT_PATHS снаружи!!!)
{
	char	*tmp;
	char	*path;
	char	*cmd_name;
	int		i;

	cmd_name = (char *)(*(cmd_elem->args_lst))->val; //первый элемент
	if (!cmd_name) //убрать так как проверка на нулл выше
	{
		printf("error: cmd is null!\n");
		return (NULL);
	}
	if (access(cmd_name, X_OK | F_OK) != -1)
		return (ft_strdup(cmd_name)); //leaks
	i = 0;
//	printf("cmd = %s\n", cmd_name);
	while (root_paths[i])
	{
		tmp = ft_strjoin(root_paths[i++], "/"); //leaks тут точно
		path = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (access(path, X_OK | F_OK) != -1)
			return (path); //leaks
		free(path);
	}
	return (NULL);
}

int **open_pipes(int len) //создаю массив из пайпов, пайпов меньше на один чем команд как максимум
{
	int		**pipe_array;
	int		pipe_fd[2];
	int		i;

	
	if (len == 0) //нет пайпов
		return (NULL);
	pipe_array = (int **)malloc(sizeof(int *) * len); //leaks
	i = 0;
	while (i < len)
	{
		pipe_array[i] = (int *)malloc(sizeof(int) * 2); //leaks
		pipe(pipe_fd);
		pipe_array[i][0] = pipe_fd[0];
		pipe_array[i++][1] = pipe_fd[1];
	}
	pipe_array[i] = NULL;
//	pipe_print(pipe_array);
	return (pipe_array);
}

//int	get_fd_in_from_file_lst(t_list **files_in, int *pipe_array) //возвращает, дескриптор, который внесем в массив и открывает другие файлы
////может вернуть дескриптор файла, 0 или 1 оставить, 0 если хердок (флаг менять при считывании команды)
////флаг - флаг на открытие O_CREAT например
//{
//	int		fd;
////	int		len;
//	t_list	*files_head;
//
//	files_head = *files_in;
//	fd = 0;
////	len = lst_len(files_in);
//	while (files_head) //прохожу все элементы кроме последнего
//	{
//
//		if (files_in->key == REDIR_IN)
//			fd = open(files_in->val, O_RDONLY, 0644);
//		else if (files_in->key == REDIR_HEREDOC)
//			fd = 0;
//		if (fd == -1) //до первого неоткрывшегося файла дошли
//			return (-1);
//		files_head = files_head->next;
//	}
//	return (fd);
//}

//int	fd_array_new(t_list **llst, int *fd_in_array, int *fd_out_array) //делает мега массив со всеми фдшниками, в нем занесены все фдшники включая пайпы и редиректы
//{
//	t_list	*head;
//	int		i;
//
//	infile_array = (int *)malloc(sizeof(int) * lst_len(llst) + 1);
//	outfile_array = (int *)malloc(sizeof(int) * lst_len(llst) + 1);
//	head = *llst;
//	i = 0;
//	while (head)
//	{
//		infile_array[i] = ;
//		outfile_array[i] = ;
//		if (*((head->val)->files_in))
//		{
//			infile_array[i] = open()
//		}
//		else
//
//		if ()
//		i++;
//		head = head->next;
//	}
//	if (cmd->files_in)
//	{
//
//		while ()
//	}
//}




//t_cmd 	*get_cmd_from_llst(t_list **llst)
//{
//	return ((llst->val))
//}
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
	
//	printf("in_fd = %d, out_fd = %d\n", *in_fd, *out_fd);
	heredoc_parser(cmd->files_in, in_fd, *heredoc_f); //не забыть анлинк в конце команды, там если heredoc_f == 1, то in_fd заменяется
//	write(2, "ok!\n", 4);
//		printf("in_fd = %d, i = %d, *heredoc = %d\n", *in_fd, i, *heredoc_f);
	if (dup2(*in_fd, 0) == -1)
		return (ft_perror("error") - 1);
	if (dup2(*out_fd, 1) == -1)
		return (ft_perror("error") - 1);
	close_all_pipes(pipe_array); //закрыл все лишние пайпы
//	sleep(1000);
//	sleep(1000);
//к этому моменту открыли файлы и заменили все фдшники
	return (0);
}

//int	open_and_dup(t_list *llst_elem, t_vars *vars, int **pipe_array, int i)
//{
//	int	in_fd;
//	int	out_fd;
//
//	if (llst_elem->next)
//	{
//
//	}
//}


int	child_process(t_list *llst_elem, t_vars *vars, int **pipe_array, int i, int n) //vars могу вытащить из cmd так что лишний аргум
{
	char	*path_to_cmd;
	t_cmd	*cmd;
	int		in_fd;
	int		out_fd;
	char	**args_str;
	int		heredoc_f;

	
	printf("pid [%d] = {%d}\n", i, getpid());
	cmd = (t_cmd *)llst_elem->val;
	
	open_files(cmd, &in_fd, &out_fd, pipe_array, i, n, &heredoc_f); //занести все переменные  в структуру
//	sleep(1000);
//	write(2, "ok!\n", 4);
//	heredoc_parser(cmd->files_in); //heredoc парсит весь список файлов на поиск хердоков и открывает все, но только последний юзает
	//НАДО ИСПРАВИТь - dup2 фдшника heredoc запихать в open_files
	//еще в хердоке надо будет сделать отедльный хэндлер, так как там сигналы работают по-другому
	
	if (vars->envp_f)
		vars->envp = convert_lst_to_str(vars->envp_lst); //дописать пересоздание env_new в env_funcs

	root_paths_init(vars);
	path_to_cmd = compose_cmd_path(cmd, vars->root_paths);
	args_str = convert_lst_to_str(cmd->args_lst);
//	(const char *filename, char *const argv [], char *const envp[]);
//	printf("path = %s\n", path_to_cmd);
//	big_str_print(args_str);
	if (!path_to_cmd)
		return (printf("%s: command not found!\n", *args_str) * 0 - 1);
//	sleep(100);
//	write(2, "ok!\n", 4);
//	if (i)
//		sleep(7);
	if (execve(path_to_cmd, args_str, vars->envp) == -1)
		return (ft_perror("error") - 1);
}

int	exec_cmd(t_list **llst, t_vars *vars) //тут надо учесть билтин или нет и количество функций учесть(разная ситуация будет)
{
	int		pipe_fd[2];
	int		*pid_array;
	t_list	*llst_elem;
	int		i;
	int		n;
	int		status;
	int		**pipe_array;
	
	int		*in_fd;
	int		*out_fd;
	
	int ret;
	int exit_mac;

	if (!llst || !(*llst)) //потом убрать
		return (printf("error: no llst or llst_elem in exec\n"));
	llst_elem = *llst;
	n = lst_len(llst); //количество функций
	if (n == 1)
	{
		//выполнить одну команду(дописать);
		printf("single cmd\n");
//		return (0); //убрать
	}
	i = 0;
	pid_array = (int *)malloc(sizeof(int) * n); //leaks массив с пидами процессов
	pipe_array = open_pipes(n - 1); //массив с пайпами, их количество = количеству команд - 1 (для стдина и аута не нужен пайп, просто дуп2)
	while (i < n)
	{
		//ВСТАВИТЬ БИЛТИНЫ + поработать с фдшниками по-особому
		pid_array[i] = fork();
		if (pid_array[i] == 0)
			child_process(llst_elem, vars, pipe_array, i, n);
		llst_elem = llst_elem->next;
		i++;
	}
	close_all_pipes(pipe_array);
	while (i--)
	{ //вроде тоже нужен WTERMSIG(status)
//		ret_pid = waitpid(-1, &status, 0); //-1  или 0 первый аргумент?
		if (ret = waitpid(-1, &status, 0), ret == pid_array[n - 1])  //нам нужен статус последней команды
			//НЕ РАБОТАЕТ ПОЧЕМУ_ТО УСЛОВИЕ(потому что WIFEXITED(status) показывает что неудачно завершилась команда - вернуть ошибку)
		{
			exit_mac = WIFEXITED(status);
			vars->exit_status = WEXITSTATUS(status);
//
//			exit_mac = WIFSIGNALED(status);
//			vars->exit_status = WTERMSIG(status);
		}

			//вытаскивает статус выхода последней команды для $?
		
		//надо ли чистить статус каждый раз?
	}
}

















//t_builtin_ptr *choose_built_in(char *cmd, t_vars *vars) //подать cmd->args[0], возврат указателя на ф-цию
//{
//	int	i;
//
//	i = -1;
//	while (i++, vars->reserved_words[i])
//		if (strcmp(cmd, vars->reserved_words[i]))
//			return (t_builtin_ptr builtin_array[i]);
//	return (NULL);
//}





//char	*compose_path_and_find_cmd(t_vars *vars, char *cmd, int cmd_flag)
//{
//	char	*temp;
//	char	*path;
//	int		i;
//
//	i = 0;
//	if (access(cmd, X_OK | F_OK) != -1)
//		return (ft_strdup(cmd));
//	while (vars->path_var[i])
//	{
//		temp = ft_strjoin(vars->path_var[i++], "/");
//		path = ft_strjoin(temp, cmd);
//		free(temp);
//		if (access(path, X_OK | F_OK) != -1)
//			return (path);
//		free(path);
//	}
//	if (cmd_flag == 1)
//		print_child_error("error: command not found\n", vars, 1);
//	else
//		print_child_error("error: command not found\n", vars, 2);
//	return (NULL);
//}
//
//
//int	exec_cmd(t_list **llst)
//{
//	t_list	*llst_elem;
//
//	if (!llst || !(*llst))
//		return (printf("error: no llst or llst_elem in exec\n"));
//	llst_elem = *llst;
//	while (llst_elem)
//	{
//		
//		llst_elem = llst_elem->next;
//	}
//}

//ls > aboba | kek | ls
