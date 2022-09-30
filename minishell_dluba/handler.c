#include "minishell.h"

void	ft_sig_int(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	sig_init(void)
{
	signal(SIGINT, ft_sig_int);
	
	signal(SIGQUIT, SIG_IGN);
}
