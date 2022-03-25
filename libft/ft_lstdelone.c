/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:57:55 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/25 17:19:45 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstdelone2(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (lst)
		if (lst->content)
			(*del)(lst->content);
	free(lst);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	free(lst);
}
