/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:10:33 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/24 01:46:09 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	reset_error(t_data *data, t_pipe *pipes, t_list **tenv, t_clear *clear)
{
	(void)pipes;
	put_error("minishell: command not found: ", data->lexer[0], "\n");
	built_in_exit(data, tenv, clear, -42);
	data->handler = 127;
}

void	reset_ok(t_data *data, t_pipe *pipes)
{
	(void)pipes;
	data->child = 1;
	pipes = NULL;
	signalhandler();
}

void	clean_lex(t_list *lex)
{
	t_list	*tmp;

	if (!lex)
		return ;
	while (lex)
	{
		tmp = lex;
		lex = lex->next;
		free(tmp);
	}
}

void	init_var_pipe(t_data *data)
{
	data->fd = NULL;
	data->fd = pipefd(data->fd, -1, data->total);
	data->current = 0;
	data->child = 0;
	signalhandler();
}

int	update_current(t_data *data, int i)
{
	while (data->lexer[i] && data->lexer[i][0] != '|')
		i++;
	return (i + 1);
}
