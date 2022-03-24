/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:16:20 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/15 17:39:30 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear2(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	int		i;

	i = 0;
	if (!lst || !del)
		return ;
	if (*lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			if (*lst)
				ft_lstdelone2(*lst, (*del));
			*lst = temp;
			i++;
		}
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	int		i;

	i = 0;
	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if (*lst)
			ft_lstdelone(*lst, (*del));
		*lst = temp;
		i++;
	}
	free(lst);
	lst = NULL;
}
