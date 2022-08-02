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

char	*compose_cmd_args(t_cmd *cmd_elem, char **root_paths) //билтин точно нет уже, отсею выше !!!!ПОСЛЕ ЭТОГО ЗАФРИШИТЬ ROOT_PATHS снаружи!!!
{
	char	*tmp;
	char	*path;
	char	*cmd;
	int		i;

	cmd = (char *)(*(cmd_elem->args_lst))->val;
	if (!cmd) //убрать так как проверка на нулл выше
	{
		printf("error: cmd is null!\n");
		return (NULL);
	}
	if (access(cmd, X_OK | F_OK) != -1)
		return (ft_strdup(cmd));
	i = 0;
	while (root_paths[i])
	{
		tmp = ft_strjoin(root_paths[i++], "/"); //leaks тут точно
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK | F_OK) != -1)
			return (path);
		free(path);
	}
	printf("error: command not found!\n");
	return (NULL);
}







int	child_process(t_list **llst, t_vars *vars, int pipe_fd[2], int i) //vars могу вытащить из cmd так что лишний аргум
{
	if (i == 0)
	{
		dup2()
	}
	
		
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
	while (i < n)
	{
		pipe(pipe_fd);
		
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

















//t_builtin_ptr *choose_built_in(char *cmd, t_vars *vars) //подать cmd->args[0], возврат указателя на ф-цию
//{
//	int	i;
//
//	i = 0;
//	while (vars->reserved_words[i])
//	{
//		if (strcmp(cmd, vars->reserved_words[i]))
//			return (t_builtin_ptr builtin_array[i]);
//		i++;
//	}
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
