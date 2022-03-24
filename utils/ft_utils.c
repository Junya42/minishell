/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:00:19 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/23 15:00:51 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	is_charset2(char const *str, char charset)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (charset == str[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_getlen(char *str, int status)
{
	int	i;

	i = 0;
	(void) status;
	while (str[i])
		i++;
	return (i);
}

int	is_built_in(char *command)
{
	if (ft_strncmp(command, "./", 2) == 0)
		return (-1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	else if (ft_strcmp(command, "echo") == 0)
		return (1);
	else if (ft_strcmp(command, "export") == 0)
		return (1);
	else if (ft_strcmp(command, "unset") == 0)
		return (1);
	else if (ft_strcmp(command, "env") == 0)
		return (1);
	else if (ft_strcmp(command, "cd") == 0)
		return (1);
	else if (ft_strcmp(command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(command, "upgrade") == 0)
		return (1);
	return (0);
}

int	no_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

char	*add_equal(char *str)
{
	char	*tmp;

	tmp = ft_strjoin4(str, "=");
	if (!str)
		return (NULL);
	free(str);
	return (tmp);
}
