/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 02:13:51 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/24 17:13:36 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*no_match(char *find, char *wildcard)
{
	free(wildcard);
	revert_wild(find);
	return (find);
}

void	wildswap(char **wilds, int j)
{
	char	*tmp;

	if (asciistrcmp(wilds[j], wilds[j + 1]) > 0)
	{
		tmp = ft_strdup(wilds[j]);
		if (!tmp)
			return ;
		free(wilds[j]);
		wilds[j] = ft_strdup(wilds[j + 1]);
		if (!wilds[j])
			return ;
		free(wilds[j + 1]);
		wilds[j + 1] = ft_strdup(tmp);
		free(tmp);
	}
}

char	*wildclean(char	**wilds, char *unparsed)
{
	char	*wild;
	int		i;

	i = -1;
	wild = ft_strdup("");
	if (!wild)
	{
		free_array(wilds);
		return (unparsed);
	}
	while (wilds[++i])
	{
		wild = ft_strjoinspace3(wild, wilds[i], i);
		if (!wild)
		{
			free_array(wilds);
			return (unparsed);
		}
	}
	free_array(wilds);
	free(unparsed);
	return (wild);
}

char	*wildsort(char	*wildcard, char *find)
{
	char	**wilds;
	int		i;
	int		j;

	revert_wild(wildcard);
	wilds = ft_split(wildcard);
	revert_wild(find);
	if (!wilds)
		return (wildcard);
	i = -1;
	while (wilds[++i])
	{
		j = 0;
		while (wilds[j + 1])
		{
			wildswap(wilds, j);
			j++;
		}
	}
	return (wildclean(wilds, wildcard));
}

char	*wildcard(char *find, int i)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*wildc;

	dir = opendir(".");
	wildc = ft_strdup("");
	if (!wildc)
		return (NULL);
	if (dir)
	{
		while (dir)
		{
			entry = readdir(dir);
			if (!entry)
				break ;
			if (ft_strncmp(entry->d_name, ".", 1) != 0)
				if (ft_strncmp(entry->d_name, "..", 2) != 0)
					if (explorer(find, entry->d_name))
						wildc = ft_strjoinspace3(wildc, entry->d_name, i++);
		}
		closedir(dir);
	}
	if (!i)
		return (no_match(find, wildc));
	return (wildsort(wildc, find));
}
