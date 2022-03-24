/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 01:36:51 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/22 12:16:49 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	do_fix_quotes(char *s, int i, int j)
{
	if (i)
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (s[i - 1] == 32)
			{
				if (i >= 2)
					if (s[i - 2] == 34 || s[i - 2] == 39)
						s[i - 1] = -s[i - 1];
				s[i - 1] = -s[i - 1];
			}
			else if (s[i + 1])
			{
				if (s[i + 1] == 32)
					while (s[i + 1 + j] && s[i + 1 + j] == 32)
						j++;
				if (s[i + 1 + j] != '|' && s[i + j + 1] != 34
					&& s[i + 1 + j] != 39 && s[i + 1] == 32)
					s[i + 1] = -s[i + 1];
			}
		}
	}
}

char	*fix_quotes(char *str, int i, int j)
{
	if (i >= (int)ft_strlen(str))
		return (str);
	while (str[i])
	{
		j = 0;
		do_fix_quotes(str, i, j);
		i++;
	}
	return (str);
}

char	**check_pipe(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[0][0] == '|')
		{
			free_array(cmd);
			return (NULL);
		}
		if (cmd[i][0] == '|' && !cmd[i + 1])
		{
			free_array(cmd);
			return (NULL);
		}
		if (cmd[i + 1] && cmd[i][0] == '|' && cmd[i + 1][0] == '|')
		{
			free_array(cmd);
			return (NULL);
		}
		i++;
	}
	return (cmd);
}

char	*in_quote_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '>')
			&& check_quotes(str, i) == 0)
			str[i] = -62;
		if ((str[i] == '<')
			&& check_quotes(str, i) == 0)
			str[i] = -60;
		i++;
	}
	return (str);
}
