/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sadprompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 03:14:52 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/24 03:14:53 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*prompt_sshell(void)
{
	char	*line;
	char	*ptr;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	ptr = line;
	line = ft_strjoin(line, "\001\033[38;2;70;70;70m\002\ue0b6"
			"\001\033[0m\002" "\001\033[48;2;70;70;70m\002"
			"\001\033[38;2;161;48;119m\002\uf468 minishell "
			"\001\033[0m\002" "\001\033[48;2;70;70;70m\002"
			"\001\033[38;2;56;56;56m\002\ue0b1 " "\001\033[0m\002"
			"\001\033[48;2;70;70;70m\002" "\001\033[38;2;144;108;255m\002");
	if (!line)
	{
		free(ptr);
		return (NULL);
	}
	return (line);
}

char	*prompt_spath(char *line)
{
	char	cwd[2048];
	char	*ptr;
	char	*prompt;
	int		i;

	prompt = NULL;
	prompt = getcwd(cwd, sizeof(cwd));
	if (!prompt)
	{
		free(line);
		return (NULL);
	}
	i = ft_strlen(prompt) - 1;
	while (prompt[i] != '/' && i > 0)
		i--;
	ptr = line;
	line = join_prompt(line, prompt + i + 1);
	if (!line)
		free(ptr);
	return (line);
}

char	*prompt_stime(char *line, char *time)
{
	char	*ptr;

	if (!time || !line)
		return (NULL);
	time[ft_strlen(time) - 1] = '\0';
	ptr = line;
	line = ft_strjoin(line, "\001\033[48;2;70;70;70m\002"
			"\001\033[38;2;56;56;56m\002\ue0b1 " "\001\033[0m\002"
			"\001\033[48;2;70;70;70m\002" "\001\033[38;2;255;255;255m\002");
	if (!check_malloc(line, ptr))
		return (NULL);
	ptr = line;
	line = join_prompt(line, time);
	if (!check_malloc(line, ptr))
		return (NULL);
	ptr = line;
	line = ft_strjoin(line, "\001\033[0m\002\001\033[38;2;70;70;70m\002"
			"\ue0b0 \001\033[0m\002");
	if (!check_malloc(line, ptr))
		return (NULL);
	return (line);
}
