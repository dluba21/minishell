#include "minishell.h"

//t_cmd_	*compose_builtin_arg(t_cmd *cmd) //структура для вити
//{
//	t_cmd_	*new_cmd;
//	int		out;
//
////	new_cmd = (t_cmd_ *)malloc(sizeof(t_cmd_));
//	new_cmd->args = convert_lst_to_str(vars->args_lst);
//	new_cmd->out = open_files_out(cmd->files_out);
//	if (new_cmd->args_array && new_cmd->args_lst[1])
//	{
//		new_cmd->args++;
//		new_cmd->len_args = big_str_len(new_cmd->args) - 1;
//	}
//}
//
//void	reset_fd(t_vars *vars, t_cmd *cmd)
//{
//	
//}

int	is_builtin(t_vars *vars, t_cmd *cmd)
{
	int		i;

	i = -1;

	while (++i < 7)
		if (!ft_strcmp((*cmd->args_lst)->val, vars->reserved_words[i]))
			return (1);
	return (0);
}

int	exec_builtin(t_vars *vars, t_cmd *cmd) //нахуя две функции учитывая вернюю? просто надо сравнить строки в is_builtin да еще и занести в exit_status, жалко, что нельзя делать присваивание в условии :(
{
	int		i;
	int		ret;

	i = 8;
	while (i--)
	{
		if (!ft_strcmp((*cmd->args_lst)->val, vars->reserved_words[i]))
		{
			if (vars->envp_f) //nado soedinit'!!!
				vars->envp = convert_lst_to_str(vars->envp_lst);//recreate_envp()
			cmd->len_args = lst_len(cmd->args_lst);
			cmd->args_array = convert_lst_to_str(cmd->args_lst);
			ret = vars->builtin_ptr_arr[i](vars, cmd);
//			close(cmd->in_fd);
//			close(cmd->out_fd);
			return (ret);
		}
	}
	return (0);
}


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



int	child_process(t_list *llst_elem, t_vars *vars, int **pipe_array, int i, int n) //vars могу вытащить из cmd так что лишний аргум
{
	char	*path_to_cmd;
	t_cmd	*cmd;
	int		in_fd;
	int		out_fd;
//	char	**args_array;
	int		heredoc_f;

//	printf("ok!\n");
	printf("pid [%d] = {%d}\n", i, getpid());
//	write(2, "oke!\n", 5);
//	fprintf(stderr, "pid [%d] = {%d}\n",  i, getpid(), 30);
	cmd = (t_cmd *)llst_elem->val;
	
	
//	open_files(cmd, pipe_array, i, n);
	
	if (vars->envp_f) //nado soedinit'!!!
		vars->envp = convert_lst_to_str(vars->envp_lst); //дописать пересоздание env_new в env_funcs

	root_paths_init(vars);
	path_to_cmd = compose_cmd_path(cmd, vars->root_paths);
	cmd->args_array = convert_lst_to_str(cmd->args_lst);
	lst_print(cmd->args_lst);
//	(const char *filename, char *const argv [], char *const envp[]);
//	printf("path = %s\n", path_to_cmd);
//	big_str_print(args_array);
	if (!path_to_cmd)
		exit(printf("%s: command not found!\n", *cmd->args_array) * 0 - 1);
//	printf("ok!\n");
//	sleep(100);
//	write(2, "ok!\n", 4);
//	if (i)
//		sleep(7);
	
	if (pipe_array)
		close_all_pipes(pipe_array);
	if (execve(path_to_cmd, cmd->args_array, vars->envp) == -1)
		return (ft_perror("error1") - 1);
	return (0);
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
	
	
//	int		*in_fd;
//	int		*out_fd;
	
	int ret;
	int exit_mac;

	if (!llst || !(*llst)) //потом убрать
		return (printf("error: no llst or llst_elem in exec\n"));
//	llst_cmd_print(llst);
	llst_elem = *llst;
	open_heredocs(llst_elem);
	n = lst_len(llst); //количество функций
//	printf("n = %d\n", n);
	if (n == 1) //ubrat'
	{
		//выполнить одну команду(дописать);
		printf("single cmd\n");
//		return (0); //убрать
	}
	
	pid_array = (int *)malloc(sizeof(int) * n); //leaks массив с пидами процессов
	pipe_array = open_pipes(n); //массив с пайпами, их количество = количеству команд - 1 (для стдина и аута не нужен пайп, просто дуп2)
	i = -1;
	printf("main proc = %d\n", getpid());
	while (++i < n)
	{
		//ВСТАВИТЬ БИЛТИНЫ + поработать с фдшниками по-особому
		
		open_files((t_cmd *)(llst_elem->val), pipe_array, i, n);
//		write(2, "ok!\n", 4);
		if (is_builtin(vars, (t_cmd *)(llst_elem->val)))
			vars->exit_status = exec_builtin(vars, (t_cmd *)(llst_elem->val));
//			do_builtin(); ВЕРНУТЬ РЕТЕРН!!
//			printf("builtin!\n");
		else
		{
			
			pid_array[i] = fork();
			if (pid_array[i] == 0)
				child_process(llst_elem, vars, pipe_array, i, n);
			
		}
//		sleep(1000);

		dup2(vars->stdin_fd, 0);
		dup2(vars->stdout_fd, 1);
		llst_elem = llst_elem->next;
		
	}
	
//	sleep(1000);
	if (pipe_array)
		close_all_pipes(pipe_array); // мб говно идея, так как блитны могут быть и закроются невовремя, так, что билтин не успеет принять инфу, если третьим по счету стоит, например, а мб и все норм

//	sleep(1000);
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
	return (0);
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
