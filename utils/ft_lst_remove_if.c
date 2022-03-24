/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 03:35:52 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/18 04:15:00 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_doc(void)
{
	t_list	*single;
	t_clear	*tmp;

	single = g_sglt;
	if (single)
	{
		if (single->content)
		{
			tmp = single->content;
			exitdoc(tmp->data, tmp->tenv, tmp, -42);
		}
	}
}

void	lst_remove_clear(void)
{
	t_list	*curr;
	t_list	*ptr;

	curr = g_sglt;
	if (curr->next)
	{
		ptr = curr->next;
		g_sglt = ptr;
	}
	else
		g_sglt = NULL;
	free(curr);
}

void	ft_lst_remove_if(t_list **tenv, char *content)
{
	t_list	*previous;
	t_list	*current;
	t_list	*ptr;

	previous = *tenv;
	while (previous->next)
	{
		current = previous->next;
		if (ualready_exist(content, current->content) == 1)
		{
			ptr = current;
			current = current->next;
			previous->next = current;
			free(ptr);
			return ;
		}
		previous = previous->next;
	}
}
