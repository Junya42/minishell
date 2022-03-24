/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_classic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:25:33 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/24 18:55:45 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	return (check_final(wild->checker, find, curr));
}
