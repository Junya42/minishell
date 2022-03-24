/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:53:15 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/24 02:02:34 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

t_list	*g_sglt = NULL;

void	wait_process(t_data *data, int memory, int check, int status)
{
	while (waitpid(-1, &status, 0) != -1)
	{
		if (WIFEXITED(status))
		{
			data->handler = WEXITSTATUS(status);
			if (data->handler == 130 && check == 1)
				return ;
		}
		else if (WIFSIGNALED(status))
		{
			data->handler = WTERMSIG(status) + 128;
			if (data->handler == 130)
				write(2, "\n", 1);
		}
		else if (WIFSTOPPED(status))
			data->handler = WSTOPSIG(status) + 128;
		if (memory == 500)
			memory = data->handler;
		check++;
	}
	if (check)
		data->handler = memory;
	if (data->handler == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}

int	minishell_loop(t_data *data, t_list **tenv, t_clear *clear)
{
	t_pipe	*pipes;
	t_list	*lex;
	t_list	*tmp;

	while (42)
	{
		reset_ok(data, pipes);
		if ((gather_input(data, tenv, clear, 1)) == -1)
			continue ;
		lex = ft_lstrevsplit(data->lexer);
		tmp = lex;
		data->total = sizepipe(data->buffer);
		if (lex)
			pipes = pipe_init(lex, data->total, tenv);
		clear->pipe = pipes;
		clean_lex(tmp);
		if (!pipes)
		{
			reset_error(data, pipes, tenv, clear);
			continue ;
		}
		do_cmd(pipes, tenv, data, clear);
	}
	return (data->handler);
}

int	minishell(char **env)
{
	t_data	*data;
	t_list	**tenv;
	t_clear	*clear;
	char	*cmd;

	cmd = NULL;
	tenv = create_list(env);
	if (!tenv)
		return (-1);
	data = datalloc();
	if (!data)
		ft_lstclear(tenv, free);
	clear = clearalloc(tenv, data);
	if (!clear)
		return (-1);
	if (!isatty(0))
	{
		signalhandler();
		data->path = get_tenv(tenv, "PATH");
		gather_input(data, tenv, NULL, 2);
		data->path = NULL;
		read_atty(0, data, clear, cmd);
		built_in_exit(data, tenv, clear, 42);
	}
	return (minishell_loop(data, tenv, clear));
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	if (!env)
		return (6);
	if (!isatty(1))
		exit (0);
	return (minishell(env));
}
