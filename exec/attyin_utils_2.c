/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attyin_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:51:35 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/20 19:14:50 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	free_double(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

int	errno_check(void)
{
	if (errno == EACCES)
		return (-1);
	if (errno == ENAMETOOLONG)
		return (-1);
	if (errno == ENFILE)
		return (-1);
	if (errno == ENOENT)
		return (-1);
	return (1);
}

char	*cmds_to_cmd(char **cmd)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (cmd[++i])
		str = ft_strjoinspace3(str, cmd[i], i - 1);
	return (str);
}

void	free_all_bis(char **cmd, char *command, char *path, int fd)
{
	if (path != cmd[0])
		free(path);
	free_array(cmd);
	free(command);
	close(fd);
}
