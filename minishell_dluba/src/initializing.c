/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 01:47:55 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/10/01 01:58:09 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_big_str(char **big_str)
{
	char	**temp;

	temp = big_str;
	while (*big_str)
		free(*big_str++);
	free(temp);
}

char	**big_string_copy(char **big_str)
{
	int		i;
	char	**ret_str;

	i = 0;
	ret_str = NULL;
	while (big_str[i])
		i++;
	ret_str = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ret_str)
		return (NULL);
	i = 0;
	while (big_str[i])
	{
		ret_str[i] = ft_strcpy(big_str[i]);
		if (!ret_str[i])
			return (NULL);
		i++;
	}
	ret_str[i] = NULL;
	return (ret_str);
}

int	envp_init(t_vars *vars, char **envp)
{
	vars->envp = big_string_copy(envp);
	if (!vars->envp)
		return (write(2, "envp malloc error\n", 18) - 19);
	vars->envp_lst = lst_env_copy(envp);
	if (!vars->envp_lst)
		return (write(2, "envp_lst malloc error\n", 18) - 23);
	return (0);
}

void	builtin_array_creator(t_vars *vars)
{
	vars->reserved_words = (char **)malloc(sizeof(char *) * 7);
	vars->builtin_ptr_arr = (t_builtin_ptr *)malloc(sizeof(t_builtin_ptr) * 7);
	vars->reserved_words[0] = ft_strdup("echo");
	vars->reserved_words[1] = ft_strdup("cd");
	vars->reserved_words[2] = ft_strdup("pwd");
	vars->reserved_words[3] = ft_strdup("export");
	vars->reserved_words[4] = ft_strdup("unset");
	vars->reserved_words[5] = ft_strdup("env");
	vars->reserved_words[6] = ft_strdup("exit");
	vars->builtin_ptr_arr[0] = ft_echo;
	vars->builtin_ptr_arr[1] = ft_cd;
	vars->builtin_ptr_arr[2] = ft_pwd;
	vars->builtin_ptr_arr[3] = ft_export;
	vars->builtin_ptr_arr[4] = ft_unset;
	vars->builtin_ptr_arr[5] = ft_env;
	vars->builtin_ptr_arr[6] = ft_exit;
}

int	vars_initializing(t_vars *vars, char **envp)
{
	envp_init(vars, envp);
	vars->exit_status = 0;
	vars->status = 0;
	vars->term_pid = ft_itoa(16651);
	builtin_array_creator(vars);
	vars->stdin_fd = dup(0);
	vars->stdout_fd = dup(1);
	return (0);
}
