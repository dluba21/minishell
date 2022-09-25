#include "minishell1.h"

int	ft_echo(t_vars *vars, t_cmd *cmd) //нужен фдшник
{
    int	i;
	int	status;

    i = -1;
	status = 0;
	if (!ft_strcmp_(cmd->args[1], "-n"))
	{
		status = 1;
		++i;
	}
    while (++i, cmd->args[i + 1] && i < cmd->len_args)
	{
		ft_putstr_fd_(cmd->args[i + 1], cmd->out);
		if (i != cmd->len_args - 1 && cmd->args[i + 2])
			ft_putstr_fd_(" ", cmd->out);
	}
	if (!status)
		write(cmd->out, "\n", 1);
	return (0);
}

//int main(void) // тест
//{
//    t_cmd_ cmd;
//
//	cmd.args[0] = "-n";
//    cmd.args[1] = "kek";
//    cmd.len_args = 2;
//    cmd.out = 1;
//    ft_echo(&cmd);
//    return (0);
//}
