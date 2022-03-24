/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:09:29 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/14 13:02:58 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	no_redir(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '>' || cmd[i][j] == '<')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	no_redir_str(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<')
			return (0);
		i++;
	}
	return (1);
}

int	check_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
			if (str[i + 1] == '>' && str[i + 2] == '>')
				return (0);
		if (str[i] == '<')
			if (str[i + 1] == '<' && str[i + 2] == '<')
				return (0);
		if (str[i] == '<' && str[i + 1] == '>')
			return (0);
		if (str[i] == '>' && str[i + 1] == '<')
			return (0);
		else if ((str[i] == '<' && str[i + 1] == '<')
			&& str[i + 2] == '>' && str[i + 3] == '>')
			return (0);
		else if ((str[i] == '>' && str[i + 1] == '>')
			&& str[i + 2] == '<' && str[i + 3] == '<')
			return (0);
		i++;
	}
	return (1);
}

char	**no_target(char **cmd)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j + 1])
			{
				if (cmd[i][j] == '>' || cmd[i][j] == '<'
					|| (cmd[i][j] == '>' && cmd[i][j + 1] == '>')
					|| (cmd[i][j] == '<' && cmd[i][j + 1] == '<'))
					if (!cmd[i + 1] && check_quotes(cmd[i] + k, i - j) == 0)
						return (NULL);
			}
			j++;
		}
		i++;
	}
	return (cmd);
}

int	parse_redir(char **cmd)
{
	int	i;

	i = 0;
	if (no_redir(cmd))
		return (1);
	if (!no_target(cmd))
	{
		return (-1);
	}
	while (cmd[i])
	{
		if (!check_redir(cmd[i]))
			return (-1);
		if ((cmd[i][0] == '>' || cmd[i][0] == '<')
				&& (!cmd[i + 1] || cmd[i + 1][0] == '>'
				|| cmd[i + 1][0] == '<'))
			return (-1);
		i++;
	}
	return (1);
}
