/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:19:59 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/21 16:28:00 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	*pipefd(int *fd, int i, int total)
{
	fd = (int *)malloc(sizeof(int) * (2 * total));
	if (!fd)
		exit(1);
	if (i < 0)
	{
		while (++i < total)
			if (pipe(fd + i * 2) < 0)
				ft_putstr_fd("error\n", 2);
	}
	return (fd);
}

void	pipedup(t_pipe *ptr, int *fd, int i, int total)
{
	int	j;

	j = 0;
	if (ptr->next)
	{
		if (dup2(fd[i + 1], 1) < 0)
			exit(128);
	}
	if (i)
	{
		if (ptr->dir)
		{
			if (ptr->dir->doc)
				j = 0;
			else if (dup2(fd[i - 2], 0) < 0)
				exit(128);
		}
		else if (dup2(fd[i - 2], 0) < 0)
			exit(128);
	}
	while (j < 2 * total)
	{
		close(fd[j]);
		j++;
	}
}

void	do_redir_pipe(t_pipe *ptr, int *fd, int i, t_data *data)
{
	sigcallhandler();
	pipedup(ptr, fd, i, data->total);
	if (ptr->dir || ptr->next)
		make_redir(ptr, ": No such file or directory\n", data);
}

void	pipe_loop(t_data *data, t_clear *clear, t_list **tenv, t_pipe *ptr)
{
	int		i;
	pid_t	pid;

	i = 0;
	init_var_pipe(data);
	while (ptr)
	{
		if (ptr->cmd)
			if (is_built_in(ptr->cmd) == 1 && data->total <= 1 && !ptr->dir)
				break ;
		ignoresignals();
		pid = fork();
		if (pid == 0)
		{
			do_redir_pipe(ptr, data->fd, i, data);
			data->free = choose_cmd(data, clear, tenv, ptr);
		}
		ptr = ptr->next;
		data->current = update_current(data, data->current);
		data->child = data->current;
		i += 2;
	}
	clean_loop(data->fd, data->total);
	if (data->total <= 1 && ptr)
		exec_built_in2(data, clear, tenv, ptr);
}
