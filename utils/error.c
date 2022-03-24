/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 22:27:16 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/20 19:45:00 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*r_error(char *s1, char *s2, char *s3)
{
	if (s1)
	{
		write(2, s1, ft_strlen(s1));
		write(2, "\n", 1);
		free(s1);
	}
	if (s2)
		write(2, s2, ft_strlen(s2));
	if (s3)
		write(2, s3, ft_strlen(s3));
	return (NULL);
}

void	put_error(char *s1, char *s2, char *s3)
{
	if (s1)
		write(2, s1, ft_strlen(s1));
	if (s2)
		write(2, s2, ft_strlen(s2));
	if (s3)
		write(2, s3, ft_strlen(s3));
}

void	put_error_bis(DIR *dir, char *s2, char *s3, t_data *data)
{
	write(2, "minishell: ", 11);
	if (s2)
		write(2, s2, ft_strlen(s2));
	if (s3)
		write(2, s3, ft_strlen(s3));
	data->handler = 127;
	closedir(dir);
}

int	array_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !arr[0])
		return (0);
	while (arr[i])
		i++;
	return (i);
}
