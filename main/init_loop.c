/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:19:34 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/24 01:48:46 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

t_clear	*clearalloc(t_list **tenv, t_data *data)
{
	t_clear	*tmp;

	tmp = (t_clear *)ft_calloc(sizeof(t_clear), 1);
	if (!tmp)
	{
		free(data);
		ft_lstclear(tenv, free);
		return (NULL);
	}
	tmp->data = data;
	tmp->tenv = tenv;
	tmp->pipe = NULL;
	tmp->first = 0;
	return (tmp);
}

t_data	*datalloc(void)
{
	t_data	*tmp;

	tmp = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (!tmp)
		return (NULL);
	tmp->hope = NULL;
	tmp->handler = 0;
	tmp->free = -1;
	tmp->checker = -1;
	return (tmp);
}

void	create_fd(t_pipe *pipe, t_list **tenv, t_data *data, t_clear *clear)
{
	t_dir	*dir;

	while (pipe)
	{
		dir = pipe->dir;
		if (dir)
		{
			while (dir)
			{
				if (dir->doc)
					make_heredoc(dir, tenv, data, clear);
				dir = dir->next;
			}
		}
		pipe = pipe->next;
	}
}

void	do_cmd(t_pipe *pipes, t_list **tenv, t_data *data, t_clear *clear)
{
	t_pipe	*ptr;

	if (PRINT)
		printpipe(pipes);
	ptr = pipes;
	create_fd(pipes, tenv, data, clear);
	if (data->child == 1)
	{
		pipe_loop(data, clear, tenv, ptr);
		wait_process(data, 500, 0, 0);
	}
	free_and_unlink(pipes);
	built_in_exit(data, tenv, clear, data->free);
}
