/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:51:49 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/23 22:53:54 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_sadprompt(t_clear *clear)
{
	char	*line;
	char	*time;
	char	*ptr;

	line = prompt_sshell();
	if (!line)
		return (NULL);
	ptr = line;
	line = prompt_spath(line);
	if (!check_malloc(line, ptr))
		return (NULL);
	time = get_time(clear);
	if (!time)
	{
		free(line);
		return (NULL);
	}
	line = prompt_stime(line, time);
	if (!check_malloc(line, ptr))
		return (NULL);
	free(time);
	return (line);
}

char	*check_prompt(t_clear *clear)
{
	char	*line;
	char	*time;
	char	*ptr;

	line = prompt_shell();
	if (!line)
		return (NULL);
	ptr = line;
	line = prompt_path(line);
	if (!check_malloc(line, ptr))
		return (NULL);
	time = get_time(clear);
	if (!time)
	{
		free(line);
		return (NULL);
	}
	line = prompt_time(line, time);
	if (!check_malloc(line, ptr))
		return (NULL);
	free(time);
	return (line);
}

char	*choose_prompt(t_clear *clear)
{
	if (!clear->first)
	{
		ft_putstr_fd
			("type upgrade if your terminal supports Truecolor.\n", 2);
	}
	clear->first++;
	if (clear->data->handler == 0)
		return (check_prompt(clear));
	return (check_sadprompt(clear));
}
