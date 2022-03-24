/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diradd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:41:41 by cmarouf           #+#    #+#             */
/*   Updated: 2022/02/28 05:16:02 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_diradd_back(t_dir **alst, t_dir *new)
{
	t_dir	*last;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	else
	{
		last = ft_dirlast(*alst);
		last->next = new;
	}
}
