/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:14:32 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/06 18:17:23 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	unclosed_dquote_d(char *str, int len)
{
	int	i;
	int	quote;
	int	dquote;

	quote = 0;
	dquote = 0;
	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] == '\'' && !(dquote % 2) && (ft_strchr(str + i, '\'')
				|| (quote % 2)))
			quote++;
		if (str[i] == '\"' && !(quote % 2) && (ft_strchr(str + i, '\"')
				|| (dquote % 2)))
			dquote++;
		i++;
	}
	if ((dquote) == 0 && (quote) >= 2)
		return (1);
	if (!(dquote % 2))
		return (0);
	return (1);
}

int	unclosed_quote(char *str, int len)
{
	int	i;
	int	quote;
	int	dquote;

	quote = 0;
	dquote = 0;
	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] == '\'' && !(dquote % 2) && (ft_strchr(str + i, '\'')
				|| (quote % 2)))
			quote++;
		if (str[i] == '\"' && !(quote % 2) && (ft_strchr(str + i, '\"')
				|| (dquote % 2)))
			dquote++;
		i++;
	}
	if (!(quote % 2))
		return (0);
	return (1);
}

int	unclosed_dquote(char *str, int len)
{
	int	i;
	int	quote;
	int	dquote;

	quote = 0;
	dquote = 0;
	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] == '\'' && !(dquote % 2) && (ft_strchr(str + i, '\'')
				|| (quote % 2)))
			quote++;
		if (str[i] == '\"' && !(quote % 2) && (ft_strchr(str + i, '\"')
				|| (dquote % 2)))
			dquote++;
		i++;
	}
	if (!(dquote % 2))
		return (0);
	return (1);
}

int	check_quotes(char *str, int len)
{
	if (unclosed_quote(str, len) || unclosed_dquote(str, len))
		return (0);
	return (1);
}

int	re_check_quotes(char *str, char charset)
{
	int	i;
	int	start;

	start = 0;
	i = 0;
	while (str[i])
	{
		if (is_charset2(str, charset) && check_quotes(str + start, i - start))
			start = i + 1;
		i++;
	}
	if (i != start)
		return (1);
	return (0);
}
