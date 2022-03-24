/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:11:00 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/14 13:22:36 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

char	*free_and_return_null(t_redir *redir)
{
	if (redir->final_str)
		free(redir->final_str);
	return (NULL);
}

void	transform(char *str, int i, int j)
{
	while (j < i)
	{
		if (str[j] == ' ' || (str[j] >= 9 && str[j] <= 13))
			str[j] = -24;
		j++;
	}
}

char	*smart_transform(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str)
	{
		while (str[i])
		{
			if (is_charset(str[i], ' ') == 1
				&& check_quotes(str + j, i - j) == 1)
			{
				if (i != j)
					transform(str, i, j);
				j = i + 1;
			}
			i++;
		}
		if (i != j)
			transform(str, i, j);
	}
	return (treat_pipe(str));
}
