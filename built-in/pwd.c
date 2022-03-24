/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:16:56 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/06 19:36:17 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	built_in_pwd(t_data *data, int code)
{
	char	cwd[2048];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	data->handler = 0;
	if (code)
		exit (0);
}
