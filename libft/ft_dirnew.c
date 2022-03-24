/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dirnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:58:17 by cmarouf           #+#    #+#             */
/*   Updated: 2022/02/28 04:42:24 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_dir	*ft_dirnew(void)
{
	t_dir	*new;

	new = (t_dir *)malloc(sizeof(t_dir));
	if (!new)
		return (NULL);
	new->in = NULL;
	new->out = NULL;
	new->app = NULL;
	new->doc = NULL;
	new->name = NULL;
	new->next = NULL;
	return (new);
}
