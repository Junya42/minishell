/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 00:55:16 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/21 15:21:05 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*fd_name(void)
{
	char	*name;
	int		i;

	i = 5;
	while (i)
	{
		name = ft_itoa(i);
		if (access(name, F_OK) == 0)
			free(name);
		else
			break ;
		i++;
	}
	return (name);
}

void	free_buff(char *buffer, int fd, int flag)
{
	if (flag)
	{
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
	else
	{
		if (buffer)
			free(buffer);
	}
}

void	in_heredoc(int fd, t_clear *clear, t_data *data, t_dir *dir)
{
	t_parse	p;
	char	*buffer;

	p.doc = fork();
	if (p.doc == 0)
	{
		sglt_ci(clear);
		sigdoc();
		while (42)
		{
			buffer = readline("> ");
			if (buffer)
				buffer = handle_dollard_2(buffer, &p, clear->tenv, data);
			if (!buffer || ft_strcmp(buffer, dir->doc) == 0)
			{
				free_buff(buffer, fd, 0);
				break ;
			}
			else
				free_buff(buffer, fd, 42);
		}
		lst_remove_clear();
		built_in_exit(data, clear->tenv, clear, 21);
	}
	wait_process(data, 500, 0, 0);
}

void	make_heredoc(t_dir *dir, t_list **tenv, t_data *data, t_clear *clear)
{
	int		fd;
	char	*home;

	data->child = 0;
	home = get_tenv(tenv, "HOME");
	if (!home)
		dir->name = ft_strjoin3("../", fd_name());
	else if (doc_strncmp(home, "../", 15) == 0)
		dir->name = joinfile(get_tenv(tenv, "HOME"), fd_name());
	else
		dir->name = ft_strjoin3("../", fd_name());
	fd = open(dir->name, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		put_error("Error opening the file\n", NULL, NULL);
		return ;
	}
	ignoresignals();
	in_heredoc(fd, clear, data, dir);
	if (data->handler != 130)
		data->child = 1;
	dir->in = dir->name;
	dir->doc = NULL;
	close(fd);
}
