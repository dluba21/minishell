#include "minishell.h"

int	is_builtin(t_vars *vars, t_cmd *cmd)
{
	int		i;

	i = -1;
	if (!(*cmd->args_lst))
		return (0);
	while (++i < 7)
		if (!ft_strcmp((*cmd->args_lst)->val, vars->reserved_words[i]))
			return (1);
	return (0);
}

int	exec_builtin(t_vars *vars, t_cmd *cmd)
{
	int		i;
	int		ret;

	i = 8;
	while (i--)
	{
		if (!ft_strcmp((*cmd->args_lst)->val, vars->reserved_words[i]))
		{
			if (vars->envp_f)
				vars->envp = convert_lst_to_str(vars->envp_lst);
			cmd->len_args = lst_len(cmd->args_lst);
			cmd->args_array = convert_lst_to_str(cmd->args_lst);
			ret = vars->builtin_ptr_arr[i](vars, cmd);
			return (ret);
		}
	}
	return (0);
}


int	root_paths_init(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->envp[i])
	{
		if (!ft_strncmp("PATH=", vars->envp[i], 5))
		{
			vars->root_paths = ft_split(vars->envp[i] + 5, ':');
			if (!vars->root_paths)
				return (0);
			return (-1);
		}
		i++;
	}
	return (-1);
}


char	*compose_cmd_path(t_cmd *cmd_elem, char **root_paths)
{
	char	*tmp;
	char	*path;
	char	*cmd_name;
	int		i;

	cmd_name = (char *)(*(cmd_elem->args_lst))->val;
	if (!cmd_name)
		return (NULL);
	if (access(cmd_name, X_OK | F_OK) != -1)
		return (ft_strdup(cmd_name));
	i = 0;
	while (root_paths[i])
	{
		tmp = ft_strjoin(root_paths[i++], "/");
		path = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (access(path, X_OK | F_OK) != -1)
			return (path);
		free(path);
	}
	return (NULL);
}



int	child_process(t_list *llst_elem, t_vars *vars, int **pipe_array, int i, int n)
{
	char	*path_to_cmd;
	t_cmd	*cmd;
	int		in_fd;
	int		out_fd;
	int		heredoc_f;

	cmd = (t_cmd *)llst_elem->val;
	
	
	
	if (vars->envp_f)
		vars->envp = convert_lst_to_str(vars->envp_lst);

	root_paths_init(vars);
	path_to_cmd = compose_cmd_path(cmd, vars->root_paths);
	cmd->args_array = convert_lst_to_str(cmd->args_lst);
	if (!path_to_cmd)
		exit(printf("%s: command not found!\n", *cmd->args_array) * 0 - 1);
	if (pipe_array)
		close_all_pipes(pipe_array);
	if (execve(path_to_cmd, cmd->args_array, vars->envp) == -1)
		return (ft_perror("error1") - 1);
	return (0);
}

int	exec_cmd(t_list **llst, t_vars *vars)
{
	int		pipe_fd[2];
	int		*pid_array;
	t_list	*llst_elem;
	int		i;
	int		n;
	int		status;
	int		**pipe_array;
	
	
	int ret;
	int exit_mac;

	llst_elem = *llst;
	open_heredocs(llst_elem);
	n = lst_len(llst);
	
	pid_array = (int *)malloc(sizeof(int) * n);
	pipe_array = open_pipes(n);
	i = -1;
	while (++i < n)
	{
		open_files((t_cmd *)(llst_elem->val), pipe_array, i, n);
		if (is_builtin(vars, (t_cmd *)(llst_elem->val)))
			vars->exit_status = exec_builtin(vars, (t_cmd *)(llst_elem->val));
		else
		{
			pid_array[i] = fork();
			if (pid_array[i] == 0)
				child_process(llst_elem, vars, pipe_array, i, n);
		}
		dup2(vars->stdin_fd, 0);
		dup2(vars->stdout_fd, 1);
		llst_elem = llst_elem->next;
	}
	if (pipe_array)
		close_all_pipes(pipe_array);
	while (i--)
	{
		if (ret = waitpid(-1, &status, 0), ret == pid_array[n - 1])
			vars->exit_status = WEXITSTATUS(status);
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
