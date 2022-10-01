/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 02:05:29 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/10/01 02:07:34 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_counter(char *str, char c)
{
	int	i;
	int	start;
	int	end;
	int	j;

	j = 0;
	i = 0;
	while (i < ft_strlen(str))
	{
		start = i;
		while (i < ft_strlen(str) && str[i] != c)
			i++;
		end = i;
		if (end - start > 0)
			j++;
		i++;
	}
	return (j);
}

static char	**anti_leak(char **big, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(big[i++]);
	free(big);
	return (NULL);
}

static char	**big_str_creator(char *s, char c, char **big)
{
	int	start;
	int	end;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(s))
	{
		start = i;
		while (i < ft_strlen(s) && s[i] != c)
			i++;
		end = i;
		if (end - start > 0)
		{
			big[j] = ft_substr(s, start, end - start);
			if (!big[j])
				return (anti_leak(big, j));
			j++;
		}
		i++;
	}
	big[j] = NULL;
	return (big);
}

char	**ft_split(char *s, char c)
{
	char	**big;

	if (!s)
		return (NULL);
	big = (char **)malloc(sizeof(char *) * (word_counter(s, c) + 1));
	if (big == NULL)
		return (NULL);
	return (big_str_creator(s, c, big));
}
