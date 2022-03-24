/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:30:56 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/23 21:37:21 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	check_cmdpath(char *absol, t_pipe *pipe)
{
	t_pipe	*ptr;

	if (!absol)
		return (0);
	ptr = pipe;
	if (ptr)
	{
		while (ptr)
		{
			if (ptr->cmd == absol)
				return (0);
			ptr = ptr->next;
		}
	}
	return (1);
}

void	defaultcmd(t_data *data, t_list **tenv, t_pipe *ptr, t_clear *clear)
{
	data->cpath = NULL;
	gather_input(data, tenv, clear, 2);
	data->cpath = build_path(data->cpath, data->splittedpath, ptr->cmd, clear);
	if (!data->cpath)
		data->cpath = NULL;
	if (data->path)
	{
		if (data->cpath)
			exec_cmd(data->cpath, ft_split(ptr->bin), data->hope, clear);
		else
		{
			if (data->cpath)
				free(data->cpath);
			put_error((char *)ptr->cmd, ": command not found\n", NULL);
			data->handler = 127;
			built_in_exit(data, tenv, clear, 42);
		}
		free(data->hope);
	}
	else
	{
		if (data->cpath)
			exec_cmd(data->cpath, ft_split(ptr->bin), data->hope, clear);
		print_exit(ptr, data, tenv, clear);
	}
}

int	choose_cmd(t_data *data, t_clear *clear, t_list **tenv, t_pipe *ptr)
{
	if (!ptr->cmd)
		built_in_exit(data, tenv, clear, 21);
	if (is_built_in(ptr->cmd) == 0)
	{
		defaultcmd(data, tenv, ptr, clear);
		return (2);
	}
	else if (is_built_in(ptr->cmd) == 1)
	{
		if (ptr->cmd)
			exec_built_in(data, clear, tenv, ptr);
		return (0);
	}
	else
	{
		gather_input(data, tenv, clear, 2);
		get_child(data, tenv, clear);
	}
	return (2);
}
