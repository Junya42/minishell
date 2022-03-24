/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:52:57 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/23 22:54:38 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	error_parsing(t_data *data, int flag)
{
	if (flag == 1)
	{
		put_error("minishell: syntax error\n", NULL, NULL);
	}
	if (flag == 3)
	{
		put_error("minishell: parse error\n", NULL, NULL);
		free_array(data->lexer);
	}
	if (data)
	{
		data->handler = 2;
		free(data->buffer);
	}
	return (-1);
}

/* Lexing puis parsing */

int	do_parsing(t_data *data, t_list **tenv)
{
	data->buffer = check_redirs(data->buffer);
	if (!data->buffer)
		return (error_parsing(data, 1));
	data->buffer = smart_transform(data->buffer);
	data->buffer = in_quote_redir(data->buffer);
	if (check_nothing(data->buffer) == -1)
		data->buffer = parsing(data->buffer, tenv, data);
	if (!data->buffer)
		return (error_parsing(data, 0));
	data->lexer = ft_split(data->buffer);
	if (!data->lexer[0])
	{
		free(data->buffer);
		free_array(data->lexer);
		return (-1);
	}
	back_to_normal(data->lexer);
	data->lexer = check_pipe(data->lexer);
	if (!data->lexer)
		return (error_parsing(data, 1));
	if (parse_redir(data->lexer) == -1)
		return (error_parsing(data, 3));
	return (1);
}

int	print_prompt(t_data *data, t_list **tenv, t_clear *clear)
{
	char	*line;

	data->lexer = NULL;
	line = choose_prompt(clear);
	if (data->checker == -1 || !line)
		data->buffer = readline("minishell > ");
	else
		data->buffer = readline(line);
	if (line)
		free(line);
	if (data->buffer)
		if (!data->buffer[0])
			return (-1);
	if (!data->buffer)
	{
		write(2, "exit\n", 5);
		built_in_exit(data, tenv, clear, 42);
	}
	if (ft_strlen(data->buffer))
		add_history(data->buffer);
	return (1);
}

void	handle_exit(t_data *data, t_list **tenv, t_clear *clear)
{
	if (ft_strcmp(data->lexer[0], "exit") == 0)
	{
		if (data->lexer[1])
			data->handler = ft_atoi(data->lexer[1]);
		write(1, "exit\n", 5);
		built_in_exit(data, tenv, clear, 42);
	}
}

int	gather_input(t_data *data, t_list **tenv, t_clear *clear, int flag)
{
	if (flag == 1)
	{
		if (print_prompt(data, tenv, clear) == -1)
			return (-1);
		if (get_tenv(&g_sglt, "sig 130="))
		{
			data->handler = 130;
			lst_remove_clear();
		}
		if (do_parsing(data, tenv) == -1)
			return (-1);
		data->path = get_tenv(tenv, "PATH");
	}
	else if (flag == 2)
	{
		if (!data->hope)
			data->hope = ft_lstsplit(tenv);
		data->splittedpath = ft_split_path(data->path, ':');
	}
	if (data->handler == -1)
		data->handler = 0;
	return (1);
}
