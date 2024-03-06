/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:53:47 by tcoze             #+#    #+#             */
/*   Updated: 2023/11/15 21:02:08 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t			total;
	size_t			i;
	size_t			p;
	char			*out;

	i = 0;
	p = 0;
	total = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (total <= 1)
		return (ft_calloc(1, 1));
	out = malloc (sizeof(char) * total);
	if (!out)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		out[i] = s1[i];
		i++;
	}
	while (p <= ft_strlen(s2))
	{
		out[i + p] = s2[p];
		p++;
	}
	return (out);
}

char	*ft_strjoin_space(char *s1, char *s2)
{
	int		total;
	int		i;
	int		p;
	char	*out;

	i = 0;
	p = 0;
	total = ft_strlen(s1) + ft_strchr_space(s2) + 1;
	if (total <= 1)
		return (ft_calloc(1, 1));
	out = malloc (sizeof(char) * total);
	if (!out)
		return (NULL);
	while (i < (int)ft_strlen(s1))
	{
		out[i] = s1[i];
		i++;
	}
	while (p < ft_strchr_space(s2))
	{
		out[i + p] = s2[p];
		p++;
	}
	out[i + p] = '\0';
	return (out);
}
