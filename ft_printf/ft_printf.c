/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 04:14:00 by tcoze             #+#    #+#             */
/*   Updated: 2023/12/13 10:02:16 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_and_print(const char *str, va_list arg, int fd);

static int	ft_check_and_print(const char *str, va_list arg, int fd)
{
	int	a;

	if (*str == '%')
		a = ft_putchar_fd('%', fd);
	if (*str == 'c')
		a = ft_putchar_fd(va_arg(arg, int), fd);
	if (*str == 's')
		a = ft_putstr_fd(va_arg(arg, char *), fd);
	if (*str == 'p')
		a = ft_c_a(va_arg(arg, unsigned long long), "0123456789abcdef", 1, fd);
	if (*str == 'd' || *str == 'i')
		a = ft_putnbr_b(va_arg(arg, int), "0123456789", 1, fd);
	if (*str == 'u')
		a = ft_putnbr_fd(va_arg(arg, unsigned int), fd, 1);
	if (*str == 'x')
		a = ft_putnbr_b(va_arg(arg, unsigned int), "0123456789abcdef", 1, fd);
	if (*str == 'X')
		a = ft_putnbr_b(va_arg(arg, unsigned int), "0123456789ABCDEF", 1, fd);
	if (a == -1)
		return (-1);
	return (a);
}

int	ft_printf(int fd, const char *str, ...)
{
	va_list	args;
	int		len;
	int		return_print_value;

	va_start (args, str);
	len = 0;
	if (!str)
		return (-1);
	while (*str)
	{
		if (*str != '%')
			return_print_value = ft_putchar_fd(*str, fd);
		else if (*(str + 1) && *str == '%')
			return_print_value = ft_check_and_print(++str, args, fd);
		else if (!*(str + 1) && *str == '%')
			return (va_end (args), -1);
		if (return_print_value == -1)
			return (va_end (args), -1);
		str++;
		len = len + return_print_value;
	}
	return (va_end (args), len);
}
