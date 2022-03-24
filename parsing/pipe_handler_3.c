/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:30:31 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/24 02:08:12 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_tilde(t_core *c, t_list **lexer)
{
	t_list	*ptr;

	ptr = *lexer;
	if (ptr)
	{
		if (c->tilde)
			if (ft_strcmp(c->tilde, c->tmp) != 0)
				free(c->tilde);
		ptr = ptr->next;
		*lexer = ptr;
	}
}

void	add_dir(t_core *c, t_list **lexer, t_pipe *elem)
{
	t_dir	*redir;
	t_list	*ptr;

	ptr = *lexer;
	if (ft_strcmp(c->tilde, ptr->content) != 0)
	{
		free(c->tilde);
		c->tilde = NULL;
	}
	redir = ft_dirnew();
	choose_redir(ptr, redir);
	ptr = ptr->next;
	*lexer = ptr;
	ft_diradd_back(&elem->dir, redir);
	if (c->i)
		c->i--;
}

void	add_elem(t_pipe *elem, t_pipe **ptr, t_list **lexer)
{
	t_list	*tmp;

	tmp = *lexer;
	elem->bin = ft_strjoinspace(elem->cmd, elem->content);
	elem->content = arg(elem->content, elem->cmd);
	ft_pipeadd_back(ptr, elem);
	if (tmp)
	{
		tmp = tmp->next;
		*lexer = tmp;
	}
}
