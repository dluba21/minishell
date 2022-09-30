#include "minishell1.h"

//char		**change_dir_env(char *value, char **ev)
//{
//	char *var;
//
//	if (!value)
//		return (ev);
//	var = ft_strjoin_("PWD=", value);
//	ev = change_value(var, ev);
//	ft_free_line(&var);
//	return (ev);
//}
//
//char		**add_oldpwd(char **ev)
//{
//	char	*tmp;
//	char	*old_pwd;
//
//	tmp = ft_find_env("OLDPWD", ev);
//	if (tmp)
//	{
//		old_pwd = getcwd(NULL, 0);
//		tmp = ft_strjoin_("OLDPWD=", old_pwd);
//		ev = change_value(tmp, ev);
//		ft_free_line(&tmp);
//		if (old_pwd)
//			ft_free_line(&old_pwd);
//	}
//	else
//	{
//		old_pwd = getcwd(NULL, 0);
//		tmp = ft_strjoin_("OLDPWD=", old_pwd);
//		ev = add_value(tmp, ev);
//		if (tmp)
//			ft_free_line(&tmp);
//		if (old_pwd)
//			ft_free_line(&old_pwd);
//	}
//	return (ev);
//}
//
//char		**change_arg_dir(t_cmd *cmd, char **ev)
//{
//	int		res;
//	char	*tmp;
//
//	res = 0;
//	res = chdir(cmd->args_array[2]);
//	printf("ret_cd = %d, path = %s\n", res, cmd->args_array[2]);
//	/*if (res == -1)
//	{
//		g_shell.status = errno; // вывод ошибки
//		ft_putendl_fd(strerror(errno), STDERR);
//		return (ev);
//	} */
//	if (cmd->len_args > 1)
//	{
//		tmp = getcwd(NULL, 0);
//		if (!tmp)
//			return (ev);
//		ev = change_dir_env(tmp, ev);
//		ft_free_line(&tmp);
//	}
//	return (ev);
//}
//
//int	ft_cd(t_vars *vars, t_cmd *cmd)//(t_cmd_ *cmd, char **ev)
//{
//	char	*root;
//	int		res;
//
//	//errno = 0;
//	printf("built!\n");
//	vars->envp = add_oldpwd(vars->envp);
//	if (cmd->len_args == 1 || !ft_strcmp_(cmd->args_array[1], "~"))
//	{
//		root = ft_var_find("HOME", vars->envp);
//		if (!root)
//		{
//			ft_putstr_fd_("minishell: cd: HOME not set\n", 1);
//			return (0);
//		}
//		res = chdir(root);
//		vars->envp = change_dir_env(root, vars->envp);
//		ft_free_line(&root);
//	}
//	else if (cmd->len_args >= 2)
//		vars->envp = change_arg_dir(cmd, vars->envp);
//	return (0);
//}




int	chdir_part(t_vars *vars, t_cmd *cmd, char *home_path, char *path)
{
	char	*old_pwd;
	int		ret;
	
	old_pwd = getcwd(NULL, 0);
	if (!path && ft_strncmp("~", cmd->args_array[1], 1))
		path = cmd->args_array[1];
	else if (!path)
		path = ft_strjoin(home_path, ++(cmd->args_array[1]));
	if (chdir(path) == -1)
		return (ft_putstr_fd("cd: No such file or directory", cmd->out_fd) * 0 - 1);
	change_env_val_key(vars, "OLD_PWD", "OLD_PWD", old_pwd);
	change_env_val_key(vars, "PWD", "PWD", getcwd(NULL, 0));
	free(old_pwd);
	free(home_path);
	return (ret);
}


int	ft_cd(t_vars *vars, t_cmd *cmd)
{
	char	*home_path;
	char	*path;
	

	home_path = find_env_var("HOME", vars->envp);
	path = NULL;
	if (!home_path)
		return (ft_putstr_fd("cd: HOME not set\n", cmd->out_fd));
	if (lst_len(cmd->args_lst) == 1 || !ft_strcmp("~", cmd->args_array[1]))
		path = home_path;
	if (chdir_part(vars, cmd, home_path, path) == -1)
		return (127);
	return (0);
}

