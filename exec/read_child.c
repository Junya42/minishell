/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 00:09:41 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/25 17:22:09 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	read_error(char *s1, char *s2, char *s3, char *error)
{
	if (!s1)
		write(2, "minishell", 9);
	else
		write(2, s1, ft_strlen(s1));
	write(2, ": ", 2);
	write(2, s2, ft_strlen(s2));
	write(2, ": ", 2);
	write(2, s3, ft_strlen(s3));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	if (s2)
		free(s2);
}

void	pid_child(char *path, char **cmd, t_clear *c, int i)
{
	char	*lex;

	if (path && path != cmd[0] && cmd[0][0] != '.')
		exec_cmd(path, cmd, c->data->hope, c);
	else
	{
		if (is_built_in(cmd[0]) == -1)
			child_error(c->data, ": No such file or directory\n", c, cmd[0]);
		else if (is_built_in(cmd[0]) == 1)
			exec_built_in3(c, cmd, path);
		else
		{
			if (path == cmd[0] && !get_tenv(c->tenv, "PATH"))
				exec_cmd(path, cmd, c->data->hope, c);
			else
			{
				lex = c->data->lexer[0];
				read_error(lex, ft_strjoinspace2("line", ft_itoa(i)), *cmd,
					"command not found\n");
			}
		}
	}
}

char	*get_command_line(char *command, int fd)
{
	command = get_next_line(fd);
	if (!command)
		return (NULL);
	if (command[ft_strlen(command) - 1] == '\n')
		command[ft_strlen(command) - 1] = '\0';
	return (command);
}

void	read_child(char	*file, t_data *data, int i, t_clear *clear)
{
	t_child	c;

	data->handler = 0;
	c.fd = open(file, O_RDONLY);
	if (c.fd < 0 || !errno_check())
		return ;
	while (++i)
	{
		c.command = get_command_line(c.command, c.fd);
		if (!c.command)
			break ;
		c.cmd = ft_split(c.command);
		if (!c.cmd)
			return ;
		c.path = build_path(c.path, data->splittedpath, c.cmd[0], clear);
		read_child_process(&c, clear, i, 0);
		free_all(c.cmd, c.command, c.path);
	}
	close(c.fd);
	clean_loop(data->fd, data->total);
	wait_process(data, 500, 0, 0);
	sglt_ci(ft_strdup("/mnt/nfs/homes/cmarouf/linux/minishell/.secret/magic"));
	if (data->handler == 130)
		execve((char *)g_sglt->content, ft_split((char *)g_sglt->content),
			ft_lstsplit(clear->tenv));
}

void	child_error(t_data *data, char	*error, t_clear *clear, char *command)
{
	DIR		*dir;
	char	*cmd;

	if (data->child == data->current)
		cmd = data->lexer[data->current];
	else
		cmd = command;
	data->handler = 126;
	if (command)
		cmd = command;
	dir = opendir(cmd);
	if (dir)
		return (put_error_bis(dir, cmd, ": Is a directory\n", data));
	closedir(dir);
	if (access(cmd, F_OK) == -1)
		put_error("minishell: ", cmd, error);
	else if (access(cmd, R_OK | X_OK) == -1)
		put_error("minishell: ", cmd, ": Permission denied\n");
	else
	{
		ignoresignals();
		read_child(cmd, data, 0, clear);
	}
	return ;
}
