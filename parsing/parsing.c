/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:19:46 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/24 00:06:48 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	back_to_normal(char **lexer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (lexer[i])
	{
		j = 0;
		while (lexer[i][j])
		{
			if (lexer[i][j] == -24)
				lexer[i][j] = ' ';
			j++;
		}
		i++;
	}
}

char	*handle_quotes(char *str, t_parse *parse)
{
	if (!check_quotes(str, ft_strlen(str)))
	{
		free(str);
		return (NULL);
	}
	str = trim_quotes(str, parse);
	if (!str)
		return (NULL);
	return (str);
}

char	*handle_dollard(char *str, t_parse *parse, t_list **tenv, t_data *data)
{	
	if (!ft_strchr(str, '$'))
		return (str);
	parse->str = ft_strdup("");
	if (alone_dollard(str) == 1)
	{
		free(parse->str);
		return (str);
	}
	parse_dollard(str, parse, tenv, data);
	free(str);
	if (!parse->str[0]
		|| (parse->str[0] == '\"' && parse->str[1] == '\"'))
	{
		free(parse->str);
		return (NULL);
	}
	if (parse->valid != 1)
		return (parse->str);
	if (!parse->str)
		return (NULL);
	return (parse->str);
}

char	*parsing(char *str, t_list **tenv, t_data *data)
{
	t_parse	parse;

	str = handle_dollard(str, &parse, tenv, data);
	if (!str)
		return (NULL);
	str = handle_quotes(str, &parse);
	if (!str)
	{
		put_error("Syntax Error: unclosed quotes\n", NULL, NULL);
		return (NULL);
	}
	return (str);
}
