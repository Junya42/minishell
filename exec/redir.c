/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:48:14 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/10 21:30:20 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

char	*which_redir(t_dir *dir)
{
	if (dir->in)
		return ((char *)dir->in);
	if (dir->out)
		return ((char *)dir->out);
	if (dir->app)
		return ((char *)dir->app);
	if (dir->doc)
		return ((char *)dir->doc);
	return (NULL);
}

int	which_open(t_dir *dir, char *target)
{
	int	fd;

	if (!dir)
		return (0);
	if (dir->in)
		return (fd = open(target, O_RDONLY));
	if (dir->out)
		return (fd = open(target, O_WRONLY | O_TRUNC | O_CREAT, 0644));
	if (dir->app)
		return (fd = open(target, O_WRONLY | O_APPEND | O_CREAT, 0644));
	if (dir->doc)
		return (fd = open(dir->doc, O_RDWR | O_TRUNC | O_CREAT, 0644));
	return (-1);
}

int	which_std(t_dir *dir)
{
	if (dir->in)
		return (0);
	if (dir->out)
		return (1);
	if (dir->app)
		return (1);
	if (dir->doc)
		return (0);
	return (-1);
}

int	make_redir(t_pipe *pipe, char *error, t_data *data)
{
	int		fd;
	t_dir	*ptr;

	ptr = pipe->dir;
	while (ptr)
	{
		fd = which_open(ptr, which_redir(ptr));
		if (fd == -1)
		{
			fd = open("/dev/null", O_RDWR);
			if (errno == EISDIR)
				put_error("minishell: ", which_redir(ptr),
					": Is a directory\n");
			else
				put_error("minishell: ", which_redir(ptr), error);
		}
		if (fd >= -1)
		{
			dup2(fd, which_std(ptr));
			close(fd);
		}
		ptr = ptr->next;
	}
	(void)data;
	return (1);
}
