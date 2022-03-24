/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:51:31 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/23 21:19:05 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_func(int end)
{
	exit(end);
}

void	defdata(t_data *data)
{
	if (data->fd)
	{
		free(data->fd);
		data->fd = NULL;
	}
	if (data->buffer)
	{
		free(data->buffer);
		data->buffer = NULL;
	}
	if (data->lexer)
	{
		free_array(data->lexer);
		data->lexer = NULL;
	}
}

void	cmddata(t_data *data)
{
	if (data->tmppath)
	{
		free(data->tmppath);
		data->tmppath = NULL;
	}
	if (data->splittedpath)
	{
		free_array(data->splittedpath);
		data->splittedpath = NULL;
	}
	if (data->hope)
	{
		free(data->hope);
		data->hope = NULL;
	}
}

void	free_the_rest(t_data *data, t_list **tenv, t_clear *clear, int flag)
{
	t_list			**ptr;
	unsigned char	end;

	ptr = NULL;
	if (flag != 24)
		ptr = &g_sglt;
	end = data->handler;
	if (tenv)
		ft_lstclear(tenv, free);
	if (ptr)
		ft_lstclear2(ptr, free);
	free(data);
	if (flag != 'c')
		free(clear);
	exit (end);
}

void	built_in_exit(t_data *data, t_list **tenv, t_clear *clear, int flag)
{
	t_pipe	*pipe;

	pipe = NULL;
	if (flag)
		cmddata(data);
	defdata(data);
	pipe = clear->pipe;
	if (pipe)
	{
		freepipe(clear->pipe, flag);
		clear->pipe = NULL;
	}
	if (flag == 42 || flag == -42 || flag == 21 || flag == 24 || flag == 'c')
		free_the_rest(data, tenv, clear, flag);
}
