/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 01:08:26 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/20 20:16:11 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_wipe(char **res)
{
	int	i;

	i = 0;
	if (res)
	{
		if (res[i])
		{
			while (res[i])
			{
				if (res[i])
					free(res[i]);
				i++;
			}
		}
		free(res);
	}
	return (NULL);
}

void	free_pipe(t_pipe *pipe)
{
	free(pipe->content);
	free(pipe->bin);
	free(pipe);
}

void	free_and_unlink(t_pipe *pipe)
{
	t_pipe	*ptr;

	ptr = pipe;
	while (ptr)
	{
		if (ptr->dir)
		{
			if (ptr->dir->name)
			{
				unlink(ptr->dir->name);
				free(ptr->dir->name);
				ptr->dir->name = NULL;
			}
		}
		ptr = ptr->next;
	}
}

t_pipe	*freepipe(t_pipe *pipe, int flag)
{
	t_pipe	*tmp;
	t_dir	*rtmp;

	if (pipe)
	{
		while (pipe)
		{
			tmp = pipe->next;
			if (pipe->dir)
			{
				while (pipe->dir)
				{
					rtmp = pipe->dir;
					if (flag == 21 && pipe->dir->name)
						free_assign_null(pipe->dir->name);
					pipe->dir = pipe->dir->next;
					free(rtmp);
				}
			}
			ft_lstclear2(&pipe->lex, free);
			free_pipe(pipe);
			pipe = tmp;
		}
	}
	return (NULL);
}

void	free_array(char **ptr)
{
	int	i;

	i = -1;
	if (ptr)
	{
		while (ptr[++i])
		{
			if (ptr[i])
			{
				free(ptr[i]);
				ptr[i] = NULL;
			}
		}
		free(ptr);
		ptr = NULL;
	}
}
