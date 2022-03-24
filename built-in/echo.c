/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:55:21 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/20 17:37:10 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	option_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i])
		{
			if (str[i] != '\0' && str[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

void	print_echo(char **cmd, int fd, int i, int ln)
{
	while (cmd[i])
	{
		if (option_check(cmd[i]) == 1)
		{
			i++;
			ln = 1;
		}
		else
			break ;
	}
	if (cmd[i])
	{
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], fd);
			if (cmd[i + 1])
				ft_putstr_fd(" ", fd);
			i++;
		}
	}
	if (ln == 0)
		ft_putchar_fd('\n', fd);
}

void	built_in_echo(t_list *lex, int fd, t_data *data, int code)
{
	char	**cmd;

	cmd = ft_lstsplit_dup(&lex);
	if (!cmd)
		return ;
	print_echo(cmd, fd, 0, 0);
	data->handler = 0;
	free_array(cmd);
	if (code)
		exit (0);
}
