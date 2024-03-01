/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 00:41:41 by tcoze             #+#    #+#             */
/*   Updated: 2023/12/04 20:51:09 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_fd(unsigned int nb2, int fd, int i)
{
	int		return_value_print;
	long	nb;

	nb = nb2;
	if (nb > 9)
		i = ft_putnbr_fd(nb / 10, fd, ++i);
	return_value_print = ft_putchar_fd(nb % 10 + '0', 1);
	if (return_value_print == -1)
		return (-1);
	return (i);
}
