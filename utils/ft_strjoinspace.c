/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinspace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:16:21 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/23 15:08:01 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	joinloop(char *dest, char *s2, size_t i)
{
	size_t	j;

	j = 0;
	while (s2[j])
	{
		if (s2[j] == -124)
			s2[j] = 124;
		dest[i] = s2[j];
		i++;
		j++;
	}
	return (i);
}

char	*ft_strjoinspace2(char *s1, char *s2)
{
	char	*dest;
	size_t	i;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * (len) + 2);
	if (!dest)
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	dest[i++] = 32;
	i = joinloop(dest, s2, i);
	dest[i] = '\0';
	free(s2);
	return (dest);
}

char	*ft_strjoinspace3(char *s1, char *s2, int space)
{
	char	*dest;
	size_t	i;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * (len) + 2);
	if (!dest)
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	if (space)
		dest[i++] = 32;
	i = joinloop(dest, s2, i);
	dest[i] = '\0';
	free(s1);
	return (dest);
}

char	*ft_strjoinspace(char *s1, char *s2)
{
	char	*dest;
	size_t	i;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * (len) + 2);
	if (!dest)
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	dest[i++] = 32;
	i = joinloop(dest, s2, i);
	dest[i] = '\0';
	return (dest);
}

char	*join_prompt(char *s1, char *s2)
{
	char	*dest;
	size_t	i;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * (len) + 2);
	if (!dest)
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	i = joinloop(dest, s2, i);
	dest[i] = 32;
	dest[i + 1] = '\0';
	free(s1);
	return (dest);
}
