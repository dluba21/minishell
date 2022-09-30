/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 01:47:31 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/10/01 01:58:09 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		i++;
	return (i);
}

static char	*blank_kostyl(void)
{
	char	*s1;

	s1 = malloc(sizeof(char));
	if (!s1)
		return (NULL);
	s1[0] = '\0';
	return (s1);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*s1;
	int		i;
	int		str_len;

	i = 0;
	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (blank_kostyl());
	if (start + len > str_len)
		len = str_len - start;
	s1 = (char *)malloc(len + 1);
	if (!s1)
		return (NULL);
	if (start < str_len || (len + start) <= str_len)
	{
		while (i < len)
			s1[i++] = s[start++];
	}
	s1[i] = '\0';
	return (s1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
