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

int	child_process(t_list *llst_elem, t_vars *vars)
{
	t_cmd	*cmd;
	char	*path_to_cmd;

	cmd = (t_cmd *)llst_elem->val;
	vars->envp = convert_lst_to_str(vars->envp_lst);
	root_paths_init(vars);
	path_to_cmd = compose_cmd_path(cmd, vars->root_paths);
	cmd->args_array = convert_lst_to_str(cmd->args_lst);
	if (!path_to_cmd)
		exit(printf("%s: command not found!\n", *cmd->args_array) * 0 - 1);
	if (vars->pipe_array)
		close_all_pipes(vars->pipe_array);
	if (execve(path_to_cmd, cmd->args_array, vars->envp) == -1)
		return (ft_perror("error") - 1);
	return (0);
}
