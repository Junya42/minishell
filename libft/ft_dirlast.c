/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dirlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:22:15 by cmarouf           #+#    #+#             */
/*   Updated: 2022/02/26 04:48:05 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_dir	*ft_dirlast(t_dir *lst)
{
	t_dir	*last;

	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	last = lst;
	return (last);
}
