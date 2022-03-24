/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:40:52 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/24 19:10:44 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	check_occurence(t_wild *wild, char *curr, char *find)
{
	while (curr[wild->i])
	{
		if (find[wild->j] != curr[wild->i])
			return (2);
		wild->i++;
		wild->j++;
		wild->checker++;
		if (!find[wild->j])
			return (0);
		if (find[wild->j] == '*')
			return (0);
	}
	return (0);
}

int	rev_explorer(char *find, char *curr, t_wild *wild)
{
	while (curr[wild->i])
	{
		if (find[wild->j] == '*' || !find[wild->j])
		{
			wild->j = skip_wild(find, wild->j);
			if (!find[wild->j] || (find[wild->j] == 42 && !find[wild->j + 1]))
				break ;
		}
		else if (curr[wild->i] == find[wild->j])
		{
			if (check_occurence(wild, curr, find) == 2)
				return (0);
		}
		else if ((curr[wild->i] != find[wild->j]) && find[wild->j] != 42)
		{
			if (wild->j && find[wild->j - 1] == 42)
				wild->i++;
			else
				return (0);
		}
		else
			wild->i++;
	}
	return (check_final(wild->checker, find, curr));
}

int	wild_files(char	*find, char *curr)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	j = 0;
	check = 0;
	while (find[j])
	{
		if (find[j] == -42)
			check = 1;
		j++;
	}
	if (!check)
		return (0);
	while (curr[i])
	{
		if (curr[i] == 42)
			curr[i] = -curr[i];
		i++;
	}
	return (1);
}

void	revert_wild(char *find)
{
	int	i;

	i = 0;
	while (find[i])
	{
		if (find[i] == -42)
			find[i] = -find[i];
		i++;
	}
}

int	explorer(char *find, char *curr)
{
	t_wild	wild;
	int		rev;

	wild.i = 0;
	wild.j = 0;
	wild.checker = 0;
	if (check_empty(find))
		return (1);
	rev = wild_files(find, curr);
	if (rev)
		return (rev_explorer(find, curr, &wild));
	return (do_explorer(find, curr, &wild));
}
