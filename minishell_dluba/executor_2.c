#include "minishell.h"

int	choose_builtin_or_bin(t_vars *vars, t_list **llst)
{
	t_list	*llst_elem;
	int		i;

	llst_elem = *llst;
	i = -1;
	while (++i < vars->llst_len)
	{
		open_files(vars, (t_cmd *)(llst_elem->val), i);
		if (is_builtin(vars, (t_cmd *)(llst_elem->val)))
			vars->exit_status = exec_builtin(vars, (t_cmd *)(llst_elem->val));
		else
		{
			vars->pid_array[i] = fork();
			if (vars->pid_array[i] == 0)
				child_process(llst_elem, vars);
		}
		dup2(vars->stdin_fd, 0);
		dup2(vars->stdout_fd, 1);
		llst_elem = llst_elem->next;
	}
	return (0);
}

int	exec_cmd(t_list **llst, t_vars *vars)
{
	int		n;
	int		status;
	int		ret;

	open_heredocs(*llst);
	vars->llst_len = lst_len(llst);
	n = vars->llst_len;
	vars->pid_array = (int *)malloc(sizeof(int) * vars->llst_len);
	vars->pipe_array = open_pipes(vars->llst_len);
	choose_builtin_or_bin(vars, llst);
	if (vars->pipe_array)
		close_all_pipes(vars->pipe_array);
	while (n--)
	{
		ret = waitpid(-1, &status, 0);
		if (ret == vars->pid_array[vars->llst_len - 1])
			vars->exit_status = WEXITSTATUS(status);
	}
	return (0);
}
