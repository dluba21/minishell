/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 01:57:54 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/10/01 01:58:09 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(t_vars *vars, t_cmd *cmd)
{
	int		i;
	char	*key;
	char	*var;

	if (lst_len(cmd->args_lst) == 1)
		return (0 / printf("unset: not enough arguments"));
	i = 0;
	while (cmd->args_array[++i])
	{
		key = env_key_trimmer(cmd->args_array[i]);
		if (key)
		{
			var = env_var_trimmer(cmd->args_array[i]);
			if (is_var_in_env(vars->envp_lst, key))
				change_env_val_key(vars, key, key, var);
			else
				add_env_value(vars, key, var);
			free(var);
		}
		free(key);
	}
	recreate_envp(vars);
	return (0);
}
