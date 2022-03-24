/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:10:20 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/18 03:12:02 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	update_old_pwd(t_list **tenv)
{
	char	cwd[2048];
	t_list	*ptr;
	char	*oldpwd;

	ptr = *tenv;
	while (ptr)
	{
		if (ft_strstr(ptr->content, "OLDPWD="))
			break ;
		ptr = ptr->next;
	}
	if (already_exist("OLDPWD=", *tenv))
	{
		ptr->content = ft_strjoin4("OLDPWD=", getcwd(cwd, sizeof(cwd)));
		ft_lstadd_new(&g_sglt, ptr->content);
	}
	else
	{
		oldpwd = ft_strjoin4("OLDPWD=", getcwd(cwd, sizeof(cwd)));
		ft_lstadd_new(tenv, oldpwd);
		ft_lstadd_new(&g_sglt, oldpwd);
	}
}

void	update_pwd(t_list **tenv)
{
	char	cwd[2048];
	char	*pwd;
	t_list	*ptr;

	ptr = *tenv;
	while (ptr)
	{
		if (ft_strstr(ptr->content, "PWD="))
			break ;
		ptr = ptr->next;
	}
	if (already_exist("PWD=", *tenv))
	{
		ptr->content = ft_strjoin4("PWD=", getcwd(cwd, sizeof(cwd)));
		ft_lstadd_new(&g_sglt, ptr->content);
	}
	else
	{
		pwd = ft_strjoin4("PWD=", getcwd(cwd, sizeof(cwd)));
		if (!pwd)
			return ;
		ft_lstadd_new(tenv, pwd);
		ft_lstadd_new(&g_sglt, pwd);
	}
}

int	exec_cd(char *path, t_list **tenv)
{
	update_old_pwd(tenv);
	if (!path)
	{
		if (!get_tenv(tenv, "HOME"))
		{
			put_error("minishell: cd: HOME not set\n", NULL, NULL);
			return (1);
		}
		else if ((chdir(get_tenv(tenv, "HOME") + 1) == -1))
		{
			put_error("minishell: cd: ", get_tenv(tenv, "HOME") + 1,
				": No such file or directory\n");
			return (1);
		}
	}
	else
	{
		if (chdir(path) == -1)
		{
			put_error("minishell: cd: ", path, ": No such file or directory\n");
			return (1);
		}
	}
	update_pwd(tenv);
	return (0);
}

void	built_in_cd(char *path, t_list **tenv, t_data *data, int code)
{
	int	i;

	i = 0;
	if (path)
	{
		while (path[i])
		{
			if (i)
			{
				if (path[i] == 32)
				{
					put_error("minishell: cd: too many arguments\n", NULL, NULL);
					return ;
				}
			}
			i++;
		}
	}
	data->handler = exec_cd(path, tenv);
	if (code)
		exit(data->handler);
}
