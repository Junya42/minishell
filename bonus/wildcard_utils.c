/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 03:49:45 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/25 20:53:54 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_empty(char *find)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (find[i])
	{
		if (find[i] != '*')
			j = 0;
		i++;
	}
	return (j);
}

int	skip_wild(char *find, int i)
{
	if (!find[i])
		return (i);
	while (find[i] && find[i] == '*')
		i++;
	return (i);
}

int	check_wild(char *find, char *curr)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (find[i])
	{
		if (find[i] != '*')
			check++;
		i++;
	}
	return (check_last(find, curr, check));
}

int	check_final(int checker, char *find, char *curr)
{
	if (checker == check_wild(find, curr))
		return (1);
	return (0);
}

int	check_last(char	*find, char *curr, int check)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (find[i + 1])
		i++;
	if (find[i] == '*')
		return (check);
	if (ft_strlen(curr) > 1)
	{
		while (curr[j + 1])
		{
			if (curr[j] == '/')
				return (-1);
			j++;
		}
	}
	if (find[i] != curr[j])
		return (-1);
	return (check);
}
