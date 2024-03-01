/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 00:34:43 by tcoze             #+#    #+#             */
/*   Updated: 2023/12/04 20:45:13 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	j;

	if (s == NULL)
		return (write(fd, "(null)", 6));
	j = ft_strlen(s);
	return (write(fd, s, j));
}
