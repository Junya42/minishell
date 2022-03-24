/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:32:44 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/12 15:39:58 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	parse_var(t_parse *p)
{
	if (p->var[p->i] == '$')
		p->var++;
	if (p->var[p->i] == '?' && p->var[p->i - 1] == '$')
	{
		p->k = 1;
		p->i++;
	}
	while ((ft_isalnum(p->var[p->i]) || p->var[p->i] == '_') && p->k == 0)
		p->i++;
}

void	trim_dollard(char *cmd, t_parse *p, t_list **tenv, t_data *data)
{
	data->exit_code = ft_itoa(data->handler);
	if (unclosed_quote(cmd, p->var - cmd))
	{
		p->valid = 1;
		p->var = ft_strchr(p->var + 1, '$');
	}
	else
	{
		p->non_var = ft_substr(p->begin, 0, p->var - p->begin);
		p->str = ft_strjoin(p->str, p->non_var);
		free(p->non_var);
		parse_var(p);
		p->aimenv = ft_substr(p->var, 0, p->i);
		if (p->k == 0 && p->i != 0)
			p->str = ft_strjoin(p->str, get_tenv2(tenv, p->aimenv, p));
		else if (p->k == 0 && p->i == 0)
			p->str = ft_strjoin(p->str, "$");
		else if (p->k == 1)
			p->str = ft_strjoin(p->str, data->exit_code);
		free(p->aimenv);
		p->begin = p->var + p->i;
		p->var = ft_strchr(p->var + 1, '$');
	}
	free(data->exit_code);
}

void	parse_dollard(char *cmd, t_parse *parse, t_list **tenv, t_data *data)
{	
	parse->valid = 0;
	parse->begin = cmd;
	parse->var = ft_strchr(parse->begin, '$');
	while (parse->var)
	{
		parse->k = 0;
		parse->i = 0;
		trim_dollard(cmd, parse, tenv, data);
	}
	parse->str = ft_strjoin(parse->str, parse->begin);
}

int	alone_dollard(char *str)
{
	int	i;
	int	alone;
	int	not_alone;

	alone = 0;
	not_alone = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '\'' || str[i + 1] == '\"'
				|| str[i + 1] == '\0' || str[i + 1] == ' ')
				alone = 1;
			else
				not_alone = 1;
		}
		i++;
	}
	if (alone == 1 && not_alone == 0)
		return (1);
	return (0);
}
