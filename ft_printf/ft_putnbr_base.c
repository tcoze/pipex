/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:47:46 by tcoze             #+#    #+#             */
/*   Updated: 2023/12/04 20:51:01 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_b(long long nbr, char *base, int i, int fd)
{
	long long	blen;
	int			return_value_print;

	blen = ft_base_len(base);
	if (ft_test_base(blen, base) == 0 || blen == 0)
		return (-1);
	if (nbr < 0)
	{
		return_value_print = ft_putchar_fd('-', fd);
		if (return_value_print == -1)
			return (-1);
		nbr = -nbr;
		i++;
	}
	if (nbr >= blen)
		i = ft_putnbr_b(nbr / blen, base, ++i, fd);
	return_value_print = ft_putchar_fd(base[nbr % blen], fd);
	if (return_value_print == -1)
		return (-1);
	return (i);
}
