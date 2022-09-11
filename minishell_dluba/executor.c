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
//	llst_cmd_print(llst);
	llst_elem = *llst;
	n = lst_len(llst); //количество функций
//	printf("n = %d\n", n);
	if (n == 1)
	{
		//выполнить одну команду(дописать);
		printf("single cmd\n");
//		return (0); //убрать
	}
	i = 0;
	pid_array = (int *)malloc(sizeof(int) * n); //leaks массив с пидами процессов
	if (n > 1)
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
	if (n > 1)
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
