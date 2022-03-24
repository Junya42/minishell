/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:41:41 by cmarouf           #+#    #+#             */
/*   Updated: 2022/02/26 03:53:00 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

void	ft_pipeadd_back(t_pipe **alst, t_pipe *new)
{
	t_pipe	*last;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	else
	{
		last = ft_pipelast(*alst);
		last->next = new;
	}
}
