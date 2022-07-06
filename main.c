#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_vars	vars;

	if (vars_initializing(&vars, env))
		return (0);
	while (!vars->exit_f)
	{
		
	}
}
