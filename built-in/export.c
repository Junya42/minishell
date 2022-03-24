/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 23:02:08 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/20 18:17:58 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	checker(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] && s2[i]) && s1[i] != '=')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (i)
		if (s1[i] == '=' && s2[i] == '=')
			return (1);
	return (0);
}

int	check_valid(char *str, t_data *data, int code)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
	{
		put_error("export: not an identifier: ", str, "\n");
		data->handler = 1;
		if (code)
			exit (1);
		return (-1);
	}
	while (str[i] != '=' && str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			put_error("export: not valid in this context: ", str, "\n");
			data->handler = 1;
			if (code)
				exit (1);
			return (-1);
		}
		i++;
	}
	data->handler = 0;
	return (1);
}

int	do_export(char **cnt, t_list **tenv, t_data *data, t_export *export)
{
	export->check = 0;
	export->tmp = *tenv;
	while (export->tmp)
	{
		export->check = already_exist(cnt[export->i], export->tmp);
		if (export->check == 1)
			break ;
		export->tmp = export->tmp->next;
	}
	if (check_valid(cnt[export->i], data, export->exit) == -1)
	{
		export->i++;
		return (1);
	}
	if (export->check == 2)
	{
		if (no_equal(cnt[export->i]))
			cnt[export->i] = add_equal(cnt[export->i]);
		export->ptr = ft_strdup(cnt[export->i]);
		if (!export->ptr)
			return (-2);
		ft_lstadd_new(tenv, export->ptr);
		ft_lstadd_new(&g_sglt, export->ptr);
	}
	return (1);
}

void	built_in_export(t_list **tenv, t_list *lex, t_data *data, int code)
{
	char		**cnt;
	t_export	export;
	int			i;

	cnt = ft_lstsplit_dup(&lex);
	i = 0;
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
