/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:58:21 by tcoze             #+#    #+#             */
/*   Updated: 2024/02/24 00:05:38 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_printf(int fd, const char *str, ...);
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
int		ft_putnbr_fd(unsigned int nb2, int fd, int i);
int		ft_putnbr_b(long long nbr, char *base, int i, int fd);
int		ft_base_len(char *base);
int		ft_test_base(int len, char *base);
int		ft_c_a(unsigned long long nbr, char *base, int i, int fd);

#endif
