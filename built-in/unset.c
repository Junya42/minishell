/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 23:44:59 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/16 15:19:52 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	ualready_exist(char *content, char *str)
{
	if (ft_strcmp("_", content) == 0)
		return (0);
	if (ft_strstr(str, content))
		return (1);
	return (0);
}

void	built_in_unset(t_list **tenv, t_list *lex, t_data *data, int code)
{
	char	**cnt;
	int		i;

	i = -1;
	if (!lex)
	{
		data->handler = 0;
		put_error("unset: not enough arguments\n", NULL, NULL);
		return ;
	}
	cnt = ft_lstsplit_dup(&lex);
	if (!cnt)
		return ;
	while (cnt[++i])
		ft_lst_remove_if(tenv, cnt[i]);
	free_array(cnt);
	data->handler = 0;
	if (code)
		exit (0);
}
