#include "../minishell.h"

int	chdir_part(t_vars *vars, t_cmd *cmd, char *home_path, char *path)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!path && ft_strncmp("~", cmd->args_array[1], 1))
		path = cmd->args_array[1];
	else if (!path)
		path = ft_strjoin(home_path, ++(cmd->args_array[1]));
	if (chdir(path) == -1)
		return (ft_putstr_fd("cd: No such file or directory", \
										cmd->out_fd) * 0 - 1);
	change_env_val_key(vars, "OLD_PWD", "OLD_PWD", old_pwd);
	change_env_val_key(vars, "PWD", "PWD", getcwd(NULL, 0));
	free(old_pwd);
	free(home_path);
	return (0);
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
