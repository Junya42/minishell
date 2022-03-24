/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 01:29:45 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/22 13:07:18 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cat_quotes(char *final_str, char *str, int i, int j)
{
	char	*to_join;

	to_join = ft_substr(str, j, i - j);
	final_str = ft_strjoin2(final_str, to_join);
	free(to_join);
	return (final_str);
}

int	jump_cmd(char *str)
{
	int	i;

	i = 0;
	if (str[i])
	{
		while (str[i] && str[i] == 32)
			i++;
		while (str[i] && str[i] != 32)
			i++;
	}
	return (i + 2);
}

char	*parse_quotes(char *str, t_parse *parse, int i, int j)
{
	char		*final_str;

	str = fix_quotes(str, jump_cmd(str), 1);
	final_str = ft_strdup("");
	while (str[i])
	{
		if ((str[i] == '\"' && !(parse->quote % 2))
			&& (ft_strchr(str + i, '\"') || (parse->dquote % 2)))
		{
			parse->dquote++;
			final_str = cat_quotes(final_str, str, i, j);
			j = i + 1;
		}
		if ((str[i] == '\'' && !(parse->dquote % 2))
			&& (ft_strchr(str + i, '\'') || (parse->quote % 2)))
		{
			parse->quote++;
			final_str = cat_quotes(final_str, str, i, j);
			j = i + 1;
		}
		i++;
	}
	final_str = cat_quotes(final_str, str, i, j);
	return (final_str);
}

char	*treat_pipe(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '|') && check_quotes(str + j, i - j) == 0)
		{
			str[i] = -124;
			j = i + 1;
		}
		i++;
	}
	return (str);
}

char	*trim_quotes(char *str, t_parse *parse)
{
	char	*ptr;

	parse->quote = 0;
	parse->dquote = 0;
	ptr = str;
	str = parse_quotes(str, parse, 0, 0);
	free(ptr);
	return (str);
}
