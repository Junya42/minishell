/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:46:56 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/20 17:58:07 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	check_error(char **argument, int len, int i, int j)
{
	while (argument[i])
	{
		while (argument[j])
		{
			if (ft_isdigit(argument[i][j]) == 0)
			{
				ft_putstr_fd("exit\n", 2);
				put_error("minishell: exit: ",
					argument[i], ": numeric argument required\n");
				return (-2);
			}
			j++;
		}
		if (len > 1)
		{
			ft_putstr_fd("exit\n", 2);
			put_error("minishell: exit: too many arguments\n", NULL, NULL);
			return (-1);
		}
		i++;
	}
	return (1);
}

void	exit_handle(t_exit *exit, t_data *data, t_list **tenv, t_clear *clear)
{
	if (exit->argument[0])
		exit->error = check_error(exit->argument, exit->len, 0, 0);
	if (exit->error == -2)
	{
		data->handler = 2;
		free_array(exit->argument);
		built_in_exit(data, tenv, clear, 42);
	}
	else if (exit->error == -1)
		data->handler = 1;
	else if (exit->error == 1)
	{
		data->handler = ft_atoi(exit->argument[0]);
		free_array(exit->argument);
		built_in_exit(data, tenv, clear, 42);
	}
	else if (exit->error == 0)
	{
		free_array(exit->argument);
		built_in_exit(data, tenv, clear, 42);
	}
	free_array(exit->argument);
}

void	exit_error(t_list *lex, t_data *data, t_list **tenv, t_clear *clear)
{
	t_exit	exit;

	exit.error = 0;
	exit.argument = ft_lstsplit_dup(&lex);
	if (!exit.argument)
		return ;
	exit.len = array_size(exit.argument);
	exit_handle(&exit, data, tenv, clear);
}
