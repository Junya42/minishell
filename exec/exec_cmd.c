/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:03:14 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/23 21:31:48 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	error_exec(t_pipe *ptr)
{
	t_pipe	*tmp;

	if (ptr->next)
	{
		tmp = ptr->next;
		if (is_built_in(tmp->cmd) == 1)
			return ;
	}
}

int	exec_cmd(char *absolute_path, char **command, char **hope, t_clear *clear)
{
	if (execve(absolute_path, command, hope) == -1)
	{
		if (command)
		{
			free_array(command);
			command = NULL;
		}
		if (check_cmdpath(absolute_path, clear->pipe))
		{
			free(absolute_path);
			absolute_path = NULL;
		}
		child_error(clear->data, ": No such file or directory\n", clear, NULL);
		if (ft_strncmp("./", absolute_path, 2) == 0)
			if (clear->data != NULL)
				built_in_exit(clear->data, clear->tenv, clear, 21);
	}
	if (command)
		free_array(command);
	if (check_cmdpath(absolute_path, clear->pipe))
		free(absolute_path);
	built_in_exit(clear->data, clear->tenv, clear, 21);
	return (1);
}

void	exec_built_in2(t_data *data, t_clear *clear, t_list **tenv, t_pipe *ptr)
{
	if (ft_strcmp(ptr->cmd, "cd") == 0)
		built_in_cd(ptr->content, tenv, data, 0);
	else if (ft_strcmp(ptr->cmd, "pwd") == 0)
		built_in_pwd(data, 0);
	else if (ft_strcmp(ptr->cmd, "exit") == 0)
		exit_error(ptr->lex, data, tenv, clear);
	else if (ft_strcmp(ptr->cmd, "echo") == 0)
		built_in_echo(ptr->lex, 1, data, 0);
	else if (ft_strcmp(ptr->cmd, "export") == 0)
		built_in_export(tenv, ptr->lex, data, 0);
	else if (ft_strcmp(ptr->cmd, "unset") == 0)
		built_in_unset(tenv, ptr->lex, data, 0);
	else if (ft_strcmp(ptr->cmd, "env") == 0)
		built_in_env(*tenv, ptr->content, data, 0);
	else if (ft_strcmp(ptr->cmd, "upgrade") == 0)
		upgrade(clear->data);
}

void	exec_built_in(t_data *data, t_clear *clear, t_list **tenv, t_pipe *ptr)
{
	if (ft_strcmp(ptr->cmd, "cd") == 0)
		built_in_cd(ptr->content, tenv, data, 0);
	else if (ft_strcmp(ptr->cmd, "pwd") == 0)
		built_in_pwd(data, 0);
	else if (ft_strcmp(ptr->cmd, "exit") == 0)
		exit_error(ptr->lex, data, tenv, clear);
	else if (ft_strcmp(ptr->cmd, "echo") == 0)
		built_in_echo(ptr->lex, 1, data, 0);
	else if (ft_strcmp(ptr->cmd, "export") == 0)
		built_in_export(tenv, ptr->lex, data, 0);
	else if (ft_strcmp(ptr->cmd, "unset") == 0)
		built_in_unset(tenv, ptr->lex, data, 0);
	else if (ft_strcmp(ptr->cmd, "env") == 0)
		built_in_env(*tenv, ptr->content, data, 0);
	else if (ft_strcmp(ptr->cmd, "upgrade") == 0)
		upgrade(clear->data);
	built_in_exit(data, tenv, clear, 21);
}

void	exec_built_in3(t_clear *clear, char **cmd, char *command)
{
	char	*str;

	str = cmds_to_cmd(cmd);
	if (ft_strcmp(command, "cd") == 0)
		built_in_cd(command, clear->tenv, clear->data, 0);
	else if (ft_strcmp(command, "pwd") == 0)
		built_in_pwd(clear->data, 0);
	else if (ft_strcmp(command, "exit") == 0)
	{
		free(str);
		exit_error(clear->pipe->lex, clear->data, clear->tenv, clear);
	}
	else if (ft_strcmp(command, "echo") == 0)
		built_in_echo(clear->pipe->lex, 1, clear->data, 0);
	else if (ft_strcmp(command, "export") == 0)
		built_in_export(clear->tenv, clear->pipe->lex, clear->data, 0);
	else if (ft_strcmp(command, "unset") == 0)
		built_in_unset(clear->tenv, clear->pipe->lex, clear->data, 0);
	else if (ft_strcmp(command, "env") == 0)
		built_in_env(*clear->tenv, str, clear->data, 0);
	else if (ft_strcmp(command, "upgrade") == 0)
		upgrade(clear->data);
	free(str);
}
