/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:49:27 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/17 07:06:42 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

unsigned char	is_maj(char c)
{
	if (c >= 65 && c <= 90)
		return ((unsigned char)(c + 32));
	return ((unsigned char)c);
}

int	asciistrcmp(char *s1, char *s2)
{
	int	i;
	int	a;
	int	b;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i] && s2[i])
	{
		a = is_maj(s1[i]);
		b = is_maj(s2[i]);
		if (a != b)
			return (a - b);
		i++;
	}
	return (is_maj(s1[i]) - is_maj(s2[i]));
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		}
		i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
