/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:47:55 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/21 17:47:57 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	sizepipe(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 1;
	while (str[i])
		if (str[i++] == 124)
			size++;
	return (size);
}

char	*skip(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] < 9 && str[i] > 13) || str[i] != 32))
		i++;
	if (!str[i])
		return (NULL);
	return (&str[i + 1]);
}

char	*arg(char *s1, char *cmd)
{
	int		checker;
	int		i;

	i = -1;
	checker = 0;
	while (s1[++i])
	{
		if (s1[i] == '=')
			checker++;
	}
	if (s1[0])
		if (cmd)
			if (!checker && ft_strcmp(cmd, "export") == 0)
				s1 = ft_strjoin(s1, "=");
	if (!s1[0])
	{
		free(s1);
		return (NULL);
	}
	return (s1);
}

t_pipe	*elem_init(void)
{
	t_pipe	*elem;

	elem = (t_pipe *)malloc(sizeof(t_pipe));
	if (!elem)
		return (NULL);
	elem->bin = NULL;
	elem->cmd = NULL;
	elem->content = ft_strdup("");
	elem->dir = NULL;
	elem->lex = NULL;
	elem->next = NULL;
	return (elem);
}

int	ischarset(char *str, char *set)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == str[i])
				return (1);
			j++;
		}
		if (str[i] == -60 || str[i] == -62 || str[i] == -32 || str[i] == -124)
			str[i] = -str[i];
		i++;
	}
	return (0);
}
