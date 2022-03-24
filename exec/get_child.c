/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 00:00:12 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/16 14:57:05 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_lvl(t_list **tenv)
{
	t_list	*ptr;
	char	*lvl;
	char	*ires;
	int		res;

	ptr = *tenv;
	res = 0;
	while (ptr)
	{
		if (ft_strstr(ptr->content, "SHLVL="))
		{
			res = ft_atoi(((char *)ptr->content + 6));
			break ;
		}
		ptr = ptr->next;
	}
	if (!res)
		return (NULL);
	ires = ft_itoa(res + 1);
	lvl = ft_strjoin4("SHLVL=", ires);
	free(ires);
	return (lvl);
}

char	*shlvl(t_list **tenv, t_data *data)
{
	char	*tmp;

	tmp = get_lvl(tenv);
	free(data->hope);
	if (!tmp)
	{
		built_in_export_bis(tenv, tmp, data, 0);
		data->hope = ft_lstsplit(tenv);
		return (tmp);
	}
	built_in_export_bis(tenv, tmp, data, 0);
	data->hope = ft_lstsplit(tenv);
	return (tmp);
}

int	get_child(t_data *data, t_list	**tenv, t_clear *clear)
{
	char	**args;
	int		code;
	char	*cmd;
	char	*lvl;
	int		status;

	args = data->lexer;
	lvl = shlvl(tenv, data);
	cmd = data->lexer[data->current];
	if (execve(cmd, args, data->hope) == -1)
	{
		free(lvl);
		child_error(data, ": No such file or directory\n", clear, NULL);
		built_in_exit(clear->data, clear->tenv, clear, 42);
	}
	if (WIFEXITED(status))
	{
		code = WEXITSTATUS(status);
		data->handler = code;
		return (code);
	}
	data->handler = -4;
	return (-4);
}
