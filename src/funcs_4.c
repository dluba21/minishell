/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 01:47:37 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/10/01 01:58:09 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr(char *str, char *c)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (c[j])
		{
			if (str[i] == c[j++])
				return (i);
		}
		i++;
	}
	return (i);
}

static int	sign_checker(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

static int	long_checker(const char *str, int i, int sign)
{
	int			len;
	long int	mod;

	mod = 0;
	len = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (sign == -1 && ((mod == 922337203685477580 && \
		(str[i] - '0' >= 8)) || len >= 19))
			return (0);
		if (sign == 1 && ((mod == 922337203685477580 \
		&& (str[i] - '0' >= 7)) || len >= 19))
			return (-1);
		mod = mod * 10 + str[i++] - '0';
		len++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	sign;
	int	mod;

	i = 0;
	j = 0;
	mod = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (j > 0)
			return (0);
		sign = sign_checker(str[i++]);
		j++;
	}
	if (long_checker(str, i, sign) < 1)
		return (long_checker(str, i, sign));
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		mod = mod * 10 + str[i++] - '0';
	return (mod * sign);
}
