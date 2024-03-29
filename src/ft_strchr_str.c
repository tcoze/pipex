/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:15:56 by tcoze             #+#    #+#             */
/*   Updated: 2023/11/14 03:39:33 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strchr_str(char *s, char *c)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (s[i] == c[j])
		{
			i++;
			j++;
		}
		if (c[j] == '\0')
			return (s + i);
		i++;
	}
	return (NULL);
}

int	ft_strchr(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strchr_space(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != ' ')
	{
		i++;
	}
	return (i);
}
