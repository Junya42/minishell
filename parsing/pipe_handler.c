/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:28:35 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/25 19:13:44 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

t_pipe	*init_init(t_core *c, t_list *lexer, int flag)
{
	t_pipe	*elem;

	if (flag == 0)
	{
		c->i = 0;
		c->checker = 0;
		elem = elem_init();
		return (elem);
	}
	if (flag == 1)
	{
		c->tmp = lexer->content;
		c->tilde = lexer->content;
		if (check_wildcard(c->tilde))
			c->tilde = wildcard(c->tilde, 0);
		revert_wild(c->tilde);
		return (NULL);
	}
	return (NULL);
}

void	first_if(t_core *c, t_list *lexer, t_pipe *elem)
{
	if (c->tilde == lexer->content)
		elem->cmd = c->tilde;
	else
	{
		elem->cmd = first_wild(c->tilde);
		c->checker++;
		ft_lstadd_new(&g_sglt, elem->cmd);
	}
	check_colors(elem);
}

void	second_if(t_core *c, t_list *lexer, t_pipe *elem, t_list **tenv)
{
	if (ft_strlen(c->tilde) == 1 && *c->tilde == 126)
	{
		ft_lstadd_mnew(&elem->lex, get_tenv(tenv, "HOME") + 1);
		elem->content = ft_strjoinspace3(elem->content, get_tenv(tenv, "HOME")
				+ 1, c->i - 1);
	}
	else
	{
		if (c->tilde == lexer->content)
			elem->content = ft_strjoinspace3(elem->content, c->tilde, c->i - 1);
		else if (c->checker)
			elem->content = ft_strjoinspace3(elem->content,
					skip_firstwild(c->tilde), c->i - 1);
		else
			elem->content = ft_strjoinspace3(elem->content, c->tilde, c->i - 1);
		ft_lstadd_mnew(&elem->lex, c->tilde);
	}
}

t_pipe	*pipe_init(t_list *lexer, int size, t_list **tenv)
{
	t_pipe	*elem;
	t_pipe	*ptr;
	t_core	c;

	ptr = NULL;
	while (size-- && lexer)
	{
		elem = init_init(&c, lexer, 0);
		while (lexer && ft_strcmp((char *)lexer->content, "|") != 0)
		{
			init_init(&c, lexer, 1);
			if (!c.i && !ischarset(lexer->content, "><"))
				first_if(&c, lexer, elem);
			else if (!ischarset(lexer->content, "><"))
				second_if(&c, lexer, elem, tenv);
			else
				add_dir(&c, &lexer, elem);
			check_tilde(&c, &lexer);
			if (elem->cmd)
				c.i++;
		}
		add_elem(elem, &ptr, &lexer);
	}
	return (ptr);
}
