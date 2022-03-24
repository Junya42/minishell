/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 03:35:31 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/20 18:34:43 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sglt_ci(void *content)
{
	t_list	**ptr;
	t_list	*new;

	ptr = &g_sglt;
	if (content)
	{
		new = ft_lstnew(content);
		ft_lstadd_front(ptr, new);
		g_sglt = *ptr;
	}
}

void	ft_lstadd_mnew(t_list **alst, void *content)
{
	t_list	*new;

	if (content)
	{
		new = ft_lstmnew(content);
		ft_lstadd_back(alst, new);
	}
}

void	ft_lstadd_new(t_list **alst, void *content)
{
	t_list	*new;

	if (content)
	{
		new = ft_lstnew(content);
		ft_lstadd_back(alst, new);
	}
}

void	add_env_var(char **env, t_list **tmp)
{
	int		i;
	char	cwd[1024];
	char	*launch;

	i = 0;
	getcwd(cwd, sizeof(cwd));
	while (env[i])
	{
		if (ft_strncmp(env[i], "_=", 2) != 0)
			ft_lstadd_new(tmp, env[i]);
		else
		{
			launch = ft_strjoin4("_=", cwd);
			if (!launch)
				return ;
			ft_lstadd_new(tmp, launch);
			ft_lstadd_new(&g_sglt, launch);
		}
		i++;
	}
}

t_list	**create_list(char **env)
{
	t_list	**tmp;
	char	cwd[1024];
	char	*pwd;
	char	*launch;

	tmp = (t_list **)ft_calloc(sizeof(t_list *), 1);
	if (!tmp)
		return (NULL);
	getcwd(cwd, sizeof(cwd));
	if (!env[0])
	{
		pwd = ft_strjoin4("PWD=", cwd);
		ft_lstadd_new(tmp, "SHLVL=1");
		ft_lstadd_new(tmp, pwd);
		ft_lstadd_new(&g_sglt, pwd);
		launch = ft_strjoin4("_=", cwd);
		if (!launch)
			return (NULL);
		ft_lstadd_new(tmp, launch);
		ft_lstadd_new(&g_sglt, launch);
		return (tmp);
	}
	add_env_var(env, tmp);
	return (tmp);
}
