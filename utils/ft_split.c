/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cmarouf <marvin@42.fr>					 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/03/04 02:10:56 by cmarouf		   #+#	#+#			 */
/*   Updated: 2022/03/08 16:04:10 by anremiki         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */
#include "../includes/minishell.h"

int	ft_isspace(char s)
{
	if ((s >= 9 && s <= 13) || s == 32)
		return (1);
	return (0);
}

int	ft_get_size(char const *s)
{
	int	size;

	size = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			size++;
			while (*s && !ft_isspace(*s))
				s++;
		}
		else
			s++;
	}
	return (size);
}

void	ft_memorycpy(char *memory, char const *s, char *res)
{
	while (memory < s)
		*(res++) = *(memory++);
}

char	**ft_secure(char const *s, char **res, char *memory)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			memory = (char *)s;
			while (*s && !ft_isspace(*s))
				s++;
			res[i] = (char *)ft_calloc(sizeof(char), (s - memory + 2));
			if (!res[i])
				return (ft_wipe(res));
			ft_memorycpy(memory, s, res[i]);
			i++;
		}
		else
			s++;
	}
	res[i] = 0;
	return (res);
}

char	**ft_split(char const *s)
{
	char	**res;
	char	*memory;

	memory = (char *)s;
	res = (char **)malloc(sizeof(char *) * (ft_get_size(s) + 1));
	if (!res || !s)
		return (NULL);
	return (ft_secure(s, res, memory));
}
