/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 17:59:51 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/20 18:22:36 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	built_in_export_bis(t_list **tenv, char *str, t_data *data, int code)
{
	char		**cnt;
	t_export	export;
	int			i;

	i = 0;
	cnt = ft_split(str);
	if (!cnt)
		return ;
	export.check = 0;
	export.exit = code;
	export.i = 0;
	if (cnt[0])
	{
		while (cnt[i])
		{
			if (do_export(cnt, tenv, data, &export) == -2)
				return ;
			export.i++;
			i++;
		}
	}
	free_array(cnt);
	if (code)
		exit (0);
}

int	already_exist(char *content, t_list *tenv)
{
	if (!ft_strchr(content, '='))
		return (-1);
	while (tenv)
	{
		if (checker(tenv->content, content))
		{
			tenv->content = ft_strdup(content);
			if (!tenv->content)
				return (-1);
			ft_lstadd_new(&g_sglt, tenv->content);
			return (1);
		}
		tenv = tenv->next;
	}
	return (2);
}
