/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attyin_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:08:12 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/25 17:21:39 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	atty_error(t_data *data, DIR *dir, char *command, t_clear *clear)
{
	if (dir)
	{
		closedir(dir);
		put_error("minishell: ", command, ": Is a directory\n");
		exit(126);
	}
	closedir(dir);
	if (access(command, F_OK) == -1)
	{
		put_error("minishell: ", command, ": No such file or directory\n");
		exit(127);
	}
	else if (access(command, R_OK | X_OK) == -1)
	{
		put_error("minishell: ", command, ": Permission denied\n");
		exit(126);
	}
	else
	{
		read_child(command, data, 1, clear);
		exit(2);
	}
}

char	*parse_atty(char *cmd, t_data *data, t_list **tenv)
{
	char	*ptr;

	if (!cmd)
		return (r_error(NULL, "minishell: corrupted data\n", NULL));
	ptr = ft_strdup(cmd);
	if (!ptr)
		return (r_error(NULL, "minishell: corrupted data\n", NULL));
	cmd = check_redirs(cmd);
	if (!cmd)
		return (r_error(ptr, "minishell: syntax error\n", NULL));
	cmd = smart_transform(cmd);
	if (!cmd)
		return (r_error(ptr, "minishell: syntax error\n", NULL));
	cmd = in_quote_redir(cmd);
	if (!cmd)
		return (r_error(ptr, "minishell: syntax error\n", NULL));
	cmd = parsing(cmd, tenv, data);
	if (!cmd)
		return (r_error(ptr, "minishell: parse error\n", NULL));
	return (cmd);
}

void	free_all(char **cmd, char *command, char *path)
{
	if (path != cmd[0])
		free(path);
	free_array(cmd);
	free(command);
}

void	flex(int stop)
{
	(void)stop;
	write(2, "\n", 1);
	sglt_ci(ft_strdup("sig 130="));
	sglt_ci(ft_strdup(
			"mnt/nfs/homes/cmarouf/minishell/.secret/magic"));
}

void	read_child_process(t_child *c, t_clear *clear, int i, int x)
{
	x = 0;
	ignoresignals();
	c->pid = fork();
	if (c->pid == 0)
	{
		if (g_sglt)
			if (g_sglt->content && g_sglt->content != clear)
				sglt_ci(clear);
		signal(SIGINT, flex);
		while (x < 30000000)
			x++;
		x = 0;
		if (get_tenv(&g_sglt, "sig 130="))
			clear->data->handler = 130;
		if (clear->data->handler != 130)
		{
			pid_child(c->path, c->cmd, clear, i);
			free_all_bis(c->cmd, c->command, c->path, c->fd);
			built_in_exit(clear->data, clear->tenv, clear, 'c');
		}
		else
			execve((char *)g_sglt->content, ft_split((char *)g_sglt->content),
				ft_lstsplit(clear->tenv));
	}
}
