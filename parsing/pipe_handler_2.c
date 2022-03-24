/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:47:44 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/21 17:54:49 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	choose_redir(t_list *lexer, t_dir *redir)
{
	if (ft_strcmp((char *)lexer->content, ">>") == 0)
	{
		lexer = lexer->next;
		redir->app = lexer->content;
	}
	else if (ft_strcmp((char *)lexer->content, "<<") == 0)
	{
		lexer = lexer->next;
		redir->doc = lexer->content;
	}
	else if (ft_strcmp((char *)lexer->content, ">") == 0)
	{
		lexer = lexer->next;
		redir->out = lexer->content;
	}
	else if (ft_strcmp((char *)lexer->content, "<") == 0)
	{
		lexer = lexer->next;
		redir->in = lexer->content;
	}
}

void	check_colors(t_pipe *elem)
{
	int	ok;

	ok = 0;
	if (ft_strncmp(elem->cmd, "ls", 2) == 0)
		ok = 1;
	else if (ft_strncmp(elem->cmd, "dir", 3) == 0)
		ok = 1;
	else if (ft_strncmp(elem->cmd, "vdir", 4) == 0)
		ok = 1;
	else if (ft_strncmp(elem->cmd, "grep", 4) == 0)
		ok = 1;
	else if (ft_strncmp(elem->cmd, "fgrep", 5) == 0)
		ok = 1;
	else if (ft_strncmp(elem->cmd, "egrep", 5) == 0)
		ok = 1;
	if (ok == 1)
	{
		free(elem->content);
		elem->content = ft_strdup("--color=auto ");
	}
}

int	check_wildcard(char	*find)
{
	int	i;

	i = 0;
	while (find[i])
	{
		if (find[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

char	*skip_firstwild(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != 32)
		i++;
	return (str + i);
}

char	*first_wild(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != 32)
		i++;
	tmp = (char *)malloc(sizeof(char) * i + 1);
	i = -1;
	while (str[++i] && str[i] != 32)
		tmp[i] = str[i];
	tmp[i] = '\0';
	return (tmp);
}
