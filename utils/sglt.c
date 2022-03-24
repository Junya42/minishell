/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sglt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 12:18:20 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/06 18:17:24 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	**sglt(void)
{
	static t_list	**ptr = NULL;

	if (!ptr)
	{
		ptr = (t_list **)ft_calloc(sizeof(t_list *), 1);
	}
	return (ptr);
}
