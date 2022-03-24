/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 21:06:55 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/16 22:27:52 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	check_nothing(char *str)
{
	if (ft_strncmp(str, "\"\"", 2) == 0)
		return (1);
	if (ft_strncmp(str, "\'\'", 2) == 0)
		return (1);
	return (-1);
}

/* parsing des maillons, strstr puis substr apres = */
int	ft_haystack2(char c, char *charset)
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

int	ft_lstrstr2(char *str, char *to_find)
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

char	*ft_path2(char *str, char *to_find)
{
	int	i;

	i = ft_lstrstr2(str, to_find);
	if (!i)
		return (NULL);
	return (&str[i]);
}

char	*get_tenv2(t_list **tenv, char *var, t_parse *parse)
{
	t_list	*ptr;
	char	*path;

	ptr = *tenv;
	while (ptr)
	{
		path = ft_path2(ptr->content, var);
		if (path)
		{
			parse->valid = 1;
			return (path);
		}
		ptr = ptr->next;
	}
	return ("\0");
}
