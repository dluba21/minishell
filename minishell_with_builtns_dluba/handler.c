#include "minishell.h"

//void	ft_sig_quit(int id)
//{
//	void(id);
//}

//void	ft_sig_int(int id)
//{
//	(void)id;
////	ft_readline();
//}
//void sig_

//void sig_heredoc(void)
//{
//	signal(SIG, SIG_IGN);
//}

void	sig_init(void)
{
//	signal(SIGINT, ft_sig_int);
	
	signal(SIGQUIT, SIG_IGN);
}
