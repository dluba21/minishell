#include "minishell.h"

char *compose_cmd_args

char	*compose_path_and_find_cmd(t_vars *vars, char *cmd, int cmd_flag)
{
	char	*temp;
	char	*path;
	int		i;

	i = 0;
	if (access(cmd, X_OK | F_OK) != -1)
		return (ft_strdup(cmd));
	while (vars->path_var[i])
	{
		temp = ft_strjoin(vars->path_var[i++], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, X_OK | F_OK) != -1)
			return (path);
		free(path);
	}
	if (cmd_flag == 1)
		print_child_error("error: command not found\n", vars, 1);
	else
		print_child_error("error: command not found\n", vars, 2);
	return (NULL);
}


int	exec_cmd(t_list **llst)
{
	t_list	*llst_elem;

	if (!llst || !(*llst))
		return (printf("error: no llst or llst_elem in exec\n"));
	llst_elem = *llst;
	while (llst_elem)
	{
		
		llst_elem = llst_elem->next;
	}
}
