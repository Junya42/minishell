/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 21:06:55 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/06 19:33:57 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"
/* parsing des maillons, strstr puis substr apres = */
int	ft_haystack(char c, char *charset)
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

int	ft_lstrstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == to_find[j])
		{
			if (str[i + j + 1] == '=')
				return (i + j + 1);
			j++;
		}
		return (0);
	}
	return (0);
}

char	*ft_path(char *str, char *charset, char *to_find)
{
	int	i;

	i = ft_lstrstr(str, to_find);
	if (!i)
		return (NULL);
	while (!ft_haystack(str[i], charset))
		i++;
	return (&str[i]);
}

char	*get_tenv(t_list **tenv, char *var)
{
	t_list	*ptr;
	char	*path;

	ptr = *tenv;
	while (ptr)
	{
		path = ft_path(ptr->content, "=", var);
		if (path)
			return (path);
		ptr = ptr->next;
	}
	return (NULL);
}

void	built_in_env(t_list *tenv, char	*argument, t_data *data, int code)
{
	if (argument && argument[0])
	{
		put_error("env: ", argument, ": No such file or directory\n");
		if (code)
			exit (0);
		return ;
	}
	if (tenv)
	{
		if (tenv->next)
		{
			while (tenv->next)
			{
				printf("%s\n", (char *)tenv->content);
				tenv = tenv->next;
			}
			printf("%s\n", (char *)tenv->content);
		}
	}
	data->handler = 0;
	if (code)
		exit (0);
}
