/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:16:36 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/23 14:34:23 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	clean_loop(int *fd, int total)
{
	int	i;

	i = 0;
	while (i < 2 * total)
	{
		close(fd[i]);
		i++;
	}
}

void	print_exit(t_pipe *ptr, t_data *data, t_list **tenv, t_clear *clear)
{
	put_error("minishell: ", (char *)ptr->cmd, ": no such file or directory\n");
	built_in_exit(data, tenv, clear, 42);
}

void	printpipe(t_pipe *p)
{
	t_dir	*dir;
	t_list	*lex;

	while (p)
	{
		dir = p->dir;
		printf("cmd = %s\ncontent = %s\n", (char *)p->cmd, (char *)p->content);
		printf("bin = %s\n>->->->->\n", (char *)p->bin);
		lex = p->lex;
		while (lex)
		{
			printf("lex = %s\n", (char *)lex->content);
			lex = lex->next;
		}
		printf("*********\n");
		while (dir)
		{
			printf("in = %s\nout = %s\n", (char *)dir->in, (char *)dir->out);
			printf("app = %s\ndoc = %s\n", (char *)dir->app, (char *)dir->doc);
			printf("name = %s\n/////////////\n", dir->name);
			dir = dir->next;
		}
		printf("%p\n------------------------\n", p->next);
		p = p->next;
	}
}
