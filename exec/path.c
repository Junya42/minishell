/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 00:51:31 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/13 18:26:26 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_all(char *str, char *s1, char	*s2, char *s3)
{
	str = ft_strcat(str, s1);
	str = ft_strcat(str, s2);
	str = ft_strcat(str, s3);
	return (str);
}

char	*try_path(char	*newpath, char **allpath, char *cmd, t_clear *clear)
{
	int	i;

	i = 0;
	while (allpath[i] != NULL)
	{
		clear->do_free = 1;
		newpath = ft_calloc(sizeof(char), ft_strlen(allpath[i])
				+ ft_strlen(cmd) + 2);
		if (!newpath)
			return (NULL);
		newpath = join_all(newpath, allpath[i], "/", cmd);
		if (access(newpath, X_OK) == 0)
			return (newpath);
		if (access(newpath, X_OK) == -1)
			free(newpath);
		i++;
	}
	newpath = ft_strdup("");
	if (!newpath)
		return (NULL);
	return (newpath);
}

char	*build_path(char *newpath, char **allpath, char *cmd, t_clear *clear)
{
	if (allpath)
	{
		if (cmd[0] != '/')
		{
			newpath = try_path(newpath, allpath, cmd, clear);
			if (!newpath)
				return (NULL);
			if (access(newpath, X_OK) == 0)
				return (newpath);
			else
			{
				if (newpath)
					free(newpath);
				return (NULL);
			}
		}
	}
	return (cmd);
}

char	*build_path_2(char *newpath, char **allpath, char *cmd, t_clear *clear)
{
	if (allpath)
	{
		if (cmd[0] != '/')
		{
			newpath = try_path(newpath, allpath, cmd, clear);
			if (!newpath)
				return (NULL);
			if (access(newpath, X_OK) == 0)
				return (newpath);
			else
			{
				if (newpath)
					free(newpath);
				return (NULL);
			}
		}
	}
	return (cmd);
}
