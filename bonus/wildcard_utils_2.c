/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:40:52 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/22 17:00:26 by cmarouf          ###   ########.fr       */
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

int	do_explorer(char *find, char *curr, t_wild *wild)
{
	while (curr[wild->i])
	{
		if (!find[wild->j])
			break ;
		if (find[wild->j] == '*')
		{
			wild->j = skip_wild(find, wild->j);
			if (!find[wild->j])
				break ;
		}
		else if (curr[wild->i] == find[wild->j])
		{
			if (check_occurence(wild, curr, find) == 2)
				return (0);
		}
		else
			wild->i++;
	}
	if (wild->checker == check_wild(find))
	{
		if (!check_last(find, curr))
			return (0);
		return (1);
	}
	return (0);
}

int	explorer(char *find, char *curr)
{
	t_wild	wild;

	wild.i = 0;
	wild.j = 0;
	wild.checker = 0;
	if (check_empty(find))
		return (1);
	return (do_explorer(find, curr, &wild));
}
