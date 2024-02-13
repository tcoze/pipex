/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:42:50 by tcoze             #+#    #+#             */
/*   Updated: 2023/11/14 03:56:25 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;

	if (size != 0)
		if (((nmemb * size) / size) != nmemb)
			return (NULL);
	str = malloc((sizeof(char) * size) * nmemb);
	if (!str)
		return (NULL);
	ft_bzero(str, size * nmemb);
	return (str);
}
