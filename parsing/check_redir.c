/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 23:39:02 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/14 13:22:51 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	cat_redirs(char *str, t_redir *redir)
{
	if (!ft_strncmp(str + redir->i, "|", 1))
	{
		redir->final_str = ft_strjoin(redir->final_str, " | ");
		return ;
	}
	if (!ft_strncmp(str + redir->i, "<<", 2))
	{
		redir->final_str = ft_strjoin(redir->final_str, " << ");
		return ;
	}
	else if (!ft_strncmp(str + redir->i, ">>", 2))
	{
		redir->final_str = ft_strjoin(redir->final_str, " >> ");
		return ;
	}
	else if (!ft_strncmp(str + redir->i, ">", 1))
	{
		redir->final_str = ft_strjoin(redir->final_str, " > ");
		return ;
	}
	else if (!ft_strncmp(str + redir->i, "<", 1))
	{
		redir->final_str = ft_strjoin(redir->final_str, " < ");
		return ;
	}
}

void	parse_double(char *str, t_redir *redir)
{
	redir->temp = ft_substr(str, redir->start, redir->i - redir->start);
	redir->final_str = ft_strjoin(redir->final_str, redir->temp);
	free(redir->temp);
	cat_redirs(str, redir);
	redir->start = redir->i + 2;
	redir->i++;
}

void	parse_single(char *str, t_redir *redir)
{
	redir->temp = ft_substr(str, redir->start, redir->i - redir->start);
	redir->final_str = ft_strjoin(redir->final_str, redir->temp);
	free(redir->temp);
	cat_redirs(str, redir);
	redir->start = redir->i + 1;
}

void	free_stuff(t_redir *redir, char *str)
{
	free(redir->temp);
	free(str);
}

char	*check_redirs(char *str)
{
	t_redir	redir;

	redir.i = -1;
	redir.start = 0;
	redir.final_str = ft_strdup("");
	if (!str || !redir.final_str)
		return (free_and_return_null(&redir));
	while (str[++(redir.i)])
	{
		if ((ft_strncmp(str + redir.i, "|", 1) == 0
				&& check_quotes(str + redir.start, redir.i - redir.start) == 1))
			parse_single(str, &redir);
		if ((ft_strncmp(str + redir.i, ">>", 2) == 0
				|| (ft_strncmp(str + redir.i, "<<", 2) == 0))
			&& check_quotes(str + redir.start, redir.i - redir.start) == 1)
			parse_double(str, &redir);
		else if ((ft_strncmp(str + redir.i, ">", 1) == 0
				|| (ft_strncmp(str + redir.i, "<", 1) == 0))
			&& check_quotes(str + redir.start, redir.i - redir.start) == 1)
			parse_single(str, &redir);
	}
	redir.temp = ft_substr(str, redir.start, redir.i - redir.start);
	redir.final_str = ft_strjoin(redir.final_str, redir.temp);
	free_stuff(&redir, str);
	return (redir.final_str);
}
