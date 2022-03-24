/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:42:55 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/06 18:17:24 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/../includes/minishell.h"

char	**malloc_error(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

int	is_charset(char i, char c)
{
	if (i == c)
		return (1);
	return (0);
}

int	w_count(char const *s, char c)
{
	int		i;
	int		word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (is_charset(s[i], c) == 0)
		{
			if (i == 0)
				word++;
			else if (is_charset(s[i - 1], c) == 1)
				word++;
		}
		i++;
	}
	return (word);
}

char	*get_string(char const *s, char c)
{
	int		i;
	int		size;
	char	*tosplit;

	i = 0;
	size = 0;
	while ((is_charset(s[i], c) == 0 && s[i]))
	{
		size++;
		i++;
	}
	tosplit = malloc(sizeof(char) * (size + 1));
	if (!tosplit)
		return (NULL);
	i = 0;
	while (is_charset(s[i], c) == 0 && s[i])
	{
		tosplit[i] = s[i];
		i++;
	}
	tosplit[i] = '\0';
	return (tosplit);
}

char	**ft_split_path(char const *s, char c)
{
	int		i;
	int		j;
	char	**split;

	if (!s)
		return (NULL);
	i = -1;
	j = -1;
	split = malloc(sizeof(char *) * (w_count(s, c) + 1));
	if (!split)
		return (NULL);
	split[w_count(s, c)] = NULL;
	while (s[++i])
	{
		if ((is_charset(s[i], c) == 0)
			&& (i == 0 || is_charset(s[i - 1], c) == 1))
			split[++j] = get_string(&s[i], c);
		if (!split)
			return (malloc_error(split));
	}
	return (split);
}
