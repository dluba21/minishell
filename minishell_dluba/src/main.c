/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 01:49:55 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/10/01 01:58:09 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_vars	vars;
	t_list	**lexed_lst;
	t_list	**llst;
	char	*str;

	(void)argv;
	(void)argc;
	if (vars_initializing(&vars, env))
		return (0);
	while (1)
	{
		sig_init();
		str = ft_readline();
		if (*str)
		{
			lexed_lst = bash_args_lst_lexer(str, &vars);
			llst = llst_new(lexed_lst);
			exec_cmd(llst, &vars);
		}
		if (str)
			free(str);
	}
	close(vars.stdin_fd);
	close(vars.stdout_fd);
}
