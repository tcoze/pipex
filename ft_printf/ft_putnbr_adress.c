/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_adress.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:39:09 by tcoze             #+#    #+#             */
/*   Updated: 2023/12/04 20:50:49 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_adress(unsigned long long nbr, char *base, int i, int fd)
{
	unsigned long long	blen;
	int					return_value_print;

	blen = ft_base_len(base);
	if (ft_test_base(blen, base) == 0 || blen == 0)
		return (-1);
	if (nbr >= blen)
		i = ft_putnbr_b(nbr / blen, base, ++i, fd);
	return_value_print = ft_putchar_fd(base[nbr % blen], fd);
	if (return_value_print == -1)
		return (-1);
	return (i);
}

int	ft_c_a(unsigned long long nbr, char *base, int i, int fd)
{
	if (!nbr)
		return (ft_printf(fd, "(nil)"));
	ft_putstr_fd("0x", fd);
	i = ft_putnbr_adress(nbr, base, i, fd);
	return (i + 2);
}
