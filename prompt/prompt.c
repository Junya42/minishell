/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:28:14 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/24 03:12:21 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*prompt_shell(void)
{
	char	*line;
	char	*ptr;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	ptr = line;
	line = ft_strjoin(line, "\001\033[38;2;161;48;119m\002\ue0b6"
			"\001\033[0m\002" "\001\033[48;2;161;48;119m\002\uf31b minishell "
			"\001\033[0m\002" "\001\033[48;2;144;108;255m\002"
			"\001\033[38;2;161;48;119m\002\ue0b0 " "\001\033[0m\002"
			"\001\033[48;2;144;108;255m\002");
	if (!line)
	{
		free(ptr);
		return (NULL);
	}
	return (line);
}

char	*prompt_path(char *line)
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

char	*get_time(t_clear *clear)
{
	char	*time;
	pid_t	pid;
	int		fd;

	time = NULL;
	fd = open("/home/anremiki/time", O_RDWR | O_TRUNC | O_CREAT, 0644);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, 1);
		execve(ft_strdup("/usr/bin/date"),
			ft_split("date +%R"), ft_lstsplit(clear->tenv));
		exit(128);
	}
	else
		waitpid(pid, 0, 0);
	close(fd);
	fd = open("/home/anremiki/time", O_RDONLY);
	time = get_next_line(fd);
	return (time);
}

int	check_malloc(char *line, char *ptr)
{
	if (!line)
	{
		free(ptr);
		return (0);
	}
	ptr = line;
	return (1);
}

char	*prompt_time(char *line, char *time)
{
	char	*ptr;

	if (!time || !line)
		return (NULL);
	time[ft_strlen(time) - 1] = '\0';
	ptr = line;
	line = ft_strjoin(line, "\001\033[48;2;19;73;105m\002"
			"\001\033[38;2;144;108;255m\002\ue0b0 " "\001\033[0m\002"
			"\001\033[48;2;19;73;105m\002" "\001\033[38;2;255;255;255m\002");
	if (!check_malloc(line, ptr))
		return (NULL);
	ptr = line;
	line = join_prompt(line, time);
	if (!check_malloc(line, ptr))
		return (NULL);
	ptr = line;
	line = ft_strjoin(line, "\001\033[0m\002\001\033[38;2;19;73;105m\002"
			"\ue0b0 \001\033[0m\002");
	if (!check_malloc(line, ptr))
		return (NULL);
	return (line);
}
