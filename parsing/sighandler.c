/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 03:24:21 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/22 16:03:34 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigread(int stop)
{
	if (stop == 2)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		execve("./a.out", ft_split("./a.out"), NULL);
	}
}

void	sighandler(int stop)
{
	if (stop == 2)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		clear_doc();
	}
}

void	siginthandle(int stop)
{
	if (stop == 2)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		if (!get_tenv(&g_sglt, "sig 130="))
			sglt_ci(ft_strdup("sig 130="));
	}
}

void	sigdoc(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
}

void	signalhandler(void)
{
	signal(SIGINT, siginthandle);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
