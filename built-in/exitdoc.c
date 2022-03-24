/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitdoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:51:31 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/20 20:09:34 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	defaultdata(t_data *data)
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

void	cmdsdata(t_data *data)
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

void	free_lists(t_data *data, t_list **tenv, int flag)
{
	t_list	**ptr;

	ptr = NULL;
	if (flag != 24)
		ptr = &g_sglt;
	if (tenv)
		ft_lstclear(tenv, free);
	if (ptr)
		ft_lstclear2(ptr, free);
	free(data);
	exit(130);
}

void	exitdoc(t_data *data, t_list **tenv, t_clear *clear, int flag)
{
	t_pipe	*pipe;

	pipe = NULL;
	if (flag)
		cmdsdata(data);
	defaultdata(data);
	pipe = clear->pipe;
	if (pipe)
	{
		free_and_unlink(pipe);
		freepipe(clear->pipe, flag);
		clear->pipe = NULL;
	}
	if (flag == 42 || flag == -42 || flag == 21 || flag == 24)
		free_lists(data, tenv, flag);
}
