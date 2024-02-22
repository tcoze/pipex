/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:37:30 by tcoze             #+#    #+#             */
/*   Updated: 2023/11/14 03:51:48 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_freeall(char **out, size_t j);
static int	ft_checknextcset(char *s, char c);
static int	ft_count(char *string, char c);

static void	ft_freeall(char **out, size_t j)
{
	size_t	i;

	i = 0;
	while (i != j)
	{
		free(out[i]);
		i++;
	}
	free(out);
}

static int	ft_checknextcset(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	if (s[i] == c)
		return (i);
	return (i);
}

static int	ft_count(char *string, char c)
{
	size_t	j;
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (string[i])
	{
		j = 0;
		while (string[j + i] != c && string[j + i])
			j++;
		if (j != 0)
		{
			count++;
			i = i + j;
		}
		else
			i++;
	}
	return (count);
}

char	**ft_split(char *s, char c)
{
	size_t	j;
	char	**out;

	j = 0;
	out = ft_calloc(sizeof(char *), ft_count(s, c) + 1);
	if (!out)
		return (NULL);
	while (*s)
	{
		if (ft_checknextcset(s, c) != 0)
		{
			out[j] = malloc(sizeof (char) * (ft_checknextcset(s, c) + 1));
			if (!out[j])
			{
				ft_freeall(out, j);
				return (NULL);
			}
			ft_strlcpy(out[j], s, ft_checknextcset(s, c) + 1);
			s = s + ft_checknextcset(s, c);
			j++;
		}
		else
			s++;
	}
	return (out);
}
