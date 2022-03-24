/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipelast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:22:15 by cmarouf           #+#    #+#             */
/*   Updated: 2022/02/26 03:52:21 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_pipe	*ft_pipelast(t_pipe *pipe)
{
	t_pipe	*last;

	if (!pipe)
		return (pipe);
	while (pipe->next)
		pipe = pipe->next;
	last = pipe;
	return (last);
}
/*int	main(void)
{
	t_pipe *a;
	t_pipe *b;
	t_pipe *c;

	a = ft_pipenew("1");
	b = ft_pipenew("2");
	c = ft_pipenew("3");
	a->next = b;
	b->next = c;
	printf("%s\n", (char *)c->content);
}*/
