#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	
	t_vars	vars;
	t_list **huy; //udalit'
	t_list *head;
	t_list *head_2;
	t_list *head_3;
	t_list	**llst;
	t_list	*llst_elem;
	t_list	**tmp;
	char	*str;

	
	if (vars_initializing(&vars, env))
		return (0);

	
	while (1)
	{
		sig_init();
		str = ft_readline();
		if (*str)
		{
			huy = bash_args_lst_lexer(str, &vars);
			llst = llst_new(huy);
			exec_cmd(llst, &vars);
		}
		if (str)
			free(str);
	}
	close(vars.stdin_fd);
	close(vars.stdout_fd);
}
