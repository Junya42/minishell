/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:59:59 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/20 18:06:23 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

/* parsing des maillons, strstr puis substr apres = */
int	ft_haystack3(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_lstrstr3(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == to_find[j])
		{
			if (str[i + j + 1] == '=' && to_find[j + 1] == '\0')
				return (i + j + 2);
			j++;
		}
		return (0);
	}
	return (0);
}

char	*ft_path3(char *str, char *to_find)
{
	int	i;

	i = ft_lstrstr3(str, to_find);
	if (!i)
		return (NULL);
	return (&str[i]);
}

char	*get_tenv3(t_list **tenv, char *var, t_parse *parse)
{
	t_list	*ptr;
	char	*path;

	ptr = *tenv;
	while (ptr)
	{
		path = ft_path3(ptr->content, var);
		if (path)
		{
			parse->valid = 1;
			return (path);
		}
		ptr = ptr->next;
	}
	return (var);
}
