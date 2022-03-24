/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attyin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:16:27 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/13 18:06:55 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	atty_child(t_data *data, char **cmds, int i, t_clear *clear)
{
	DIR		*dir;
	char	*index;

	if (data->path && cmds[0][0] != '.')
		exec_cmd(data->path, cmds, data->hope, clear);
	else
	{
		if (is_built_in(cmds[0]) == -1)
		{
			dir = opendir(cmds[0]);
			atty_error(data, dir, cmds[0], clear);
		}
		else
		{
			index = ft_itoa(i);
			if (!index)
				return ;
			read_error(NULL, ft_strjoinspace2("line", index), *cmds,
				"command not found\n");
			free(index);
			data->handler = 127;
			built_in_exit(data, clear->tenv, clear, 42);
		}
	}
}

void	wait_atty(char **cmds, t_data *data)
{
	int	status;
	int	memory;

	memory = 0;
	while (waitpid(-1, &status, 0) != -1)
	{
		if (!memory)
			memory = data->handler;
		if (WIFEXITED(status))
			data->handler = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->handler = WTERMSIG(status) + 128;
		else if (WCOREDUMP(status))
			data->handler = 131;
		else if (WIFSTOPPED(status))
			data->handler = WSTOPSIG(status) + 128;
		else
			data->handler = -1;
	}
	data->handler = memory;
	if (cmds && cmds[0])
		free_array(cmds);
}

char	*launch_child(t_data *data, char **cmds, int i, t_clear *clear)
{
	pid_t	pid;

	data->path = build_path(data->path, data->splittedpath, cmds[0], clear);
	if (!data->path)
		return (NULL);
	pid = fork();
	if (pid == 0)
		atty_child(data, cmds, i, clear);
	if (data->path)
		free(data->path);
	return (data->path);
}

char	*get_atty(int fd, char *cmd)
{
	cmd = get_next_line(fd);
	if (!cmd)
		return (NULL);
	if (cmd[ft_strlen(cmd) - 1] == '\n')
		cmd[ft_strlen(cmd) - 1] = '\0';
	return (cmd);
}

void	read_atty(int fd, t_data *data, t_clear *clear, char *cmd)
{
	char	**cmds;
	int		i;

	i = 0;
	while (++i)
	{
		signal(SIGPIPE, SIG_IGN);
		cmd = get_atty(fd, cmd);
		if (!cmd)
			return ;
		cmd = parse_atty(cmd, data, clear->tenv);
		if (!cmd)
			break ;
		cmds = ft_split(cmd);
		if (!cmds || !cmds[0])
		{
			put_error(cmd, "\nminishell: corrupted data\n", NULL);
			break ;
		}
		launch_child(data, cmds, i, clear);
		if (cmd)
			free(cmd);
	}
}
