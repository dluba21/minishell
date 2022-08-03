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
	while (root_paths[i])
	{
		tmp = ft_strjoin(root_paths[i++], "/"); //leaks тут точно
		path = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (access(path, X_OK | F_OK) != -1)
			return (path); //leaks
		free(path);
	}
	printf("error: command not found!\n");
	return (NULL);
}



int	fd_array_new(t_cmd *cmd, int *fd_in_array, int *fd_out_array) //делает мега массив со всеми фдшниками, в нем занесены все фдшники включая пайпы и редиректы
{
	t_list	*head;

	infile_array = NULL;
	outfile_array = NULL;
	if (cmd->files_in)
	{
		infile_array = (int *)malloc(sizeof(int) * )
		while ()
	}
}




//t_cmd 	*get_cmd_from_llst(t_list **llst)
//{
//	return ((llst->val))
//}

int	child_process(t_list *llst_elem, t_vars *vars, int i) //vars могу вытащить из cmd так что лишний аргум
{
	char	*path_to_cmd;
	t_cmd	*cmd;
	int		*in_fd;
	int		*out_fd;

	
//	if (i == 0)
//	{
//		dup2()
//	}
	cmd = (t_cmd *)llst_elem->val;
	path_to_cmd = compose_cmd_path(cmd, vars->root_paths);
	if (!path_to_cmd)
		printf("command not found: %s\n", *(cmd->args_lst->val)); //исправить на ретерн
	if (env_f)
		vars->envp = env_new(); //дописать пересоздание env_new в env_funcs
	
	//закрыть все лишние пайпы
		
//	execve();
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

	if (!llst || !(*llst)) //потом убрать
		return (printf("error: no llst or llst_elem in exec\n"));
	llst_elem = *llst;
	n = lst_len(llst); //количество функций
	if (n == 1)
	{
		//выполнить одну команду(дописать);
		printf("single cmd\n");
		return (0); //убрать
	}
	i = 0;
	pid_array = (int *)malloc(sizeof(int) * n); //leaks
//	pipe_array = (int **)malloc(sizeof(int *) * );
	//создать массивы на ввод и вывод c пайпами и редиректами сразу для всех команд а анализировать буду открылось или нет уже внутри чайлда перед dup2 (проверять на -1 и если ошибка, nj ghtrhfofnm команду полностью) в том числе учесть heredoc, походу надо внести в один список с infile heredoc и в ключ занести heredoc он или нет
	while (i < n)
	{
		
		
		pid_array[i] = fork();
		if (pid_array[i] == 0)
		{
			child_process(llst, vars, i, pipe_fd);
		}
		if (pid_array[i] != 0) //мб лишняя проверка так как child точно завершится
		{
//			dup2
			llst_elem = llst_elem->next;
			i++;
		}
		
//		ft_close_all_fd();
		free(in_fd);
		free(out_fd);
	}
	while (i--)
	{ //вроде тоже нужен WTERMSIG(status)
//		ret_pid = waitpid(-1, &status, 0); //-1  или 0 первый аргумент?
		if (waitpid(-1, &status, 0) == pid_array[n - 1] && WIFEXITED(status)) //нам нужен статус последней команды
			vars->exit_status = WEXITSTATUS(status); //вытаскивает статус выхода последней команды для $?
		//надо ли чистить статус каждый раз?
		
	}
		//сначала открыть пайп
		//не найдена команда уже по ходу дела
}

















t_builtin_ptr *choose_built_in(char *cmd, t_vars *vars) //подать cmd->args[0], возврат указателя на ф-цию
{
	int	i;

	i = -1;
	while (i++, vars->reserved_words[i])
		if (strcmp(cmd, vars->reserved_words[i]))
			return (t_builtin_ptr builtin_array[i]);
	return (NULL);
}





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
