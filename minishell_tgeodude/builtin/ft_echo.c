#include "minishell.h"

void    ft_echo(t_cmd *cmd)
{
    int	i;
	int	status;

    i = -1;
	status = 0;
	if (!ft_strcmp(cmd->args[0], "-n"))
	{
		status = 1;
		++i;
	}
    while (++i, cmd->args[i] && i < cmd->len_args)
	{
        ft_putstr_fd(cmd->args[i], cmd->out);
		if (i != cmd->len_args - 1 && cmd->args[i + 1])
			ft_putstr_fd(" ", cmd->out);
	}
	if (!status)
		write(cmd->out, "\n", 1);
}

int main(void) // тест
{
    t_cmd cmd;

	cmd.args[0] = "-n";
    cmd.args[1] = "kek";
    cmd.len_args = 2;
    cmd.out = 1;
    ft_echo(&cmd);
    return (0);
}