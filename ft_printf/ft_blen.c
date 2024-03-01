/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:37:03 by tcoze             #+#    #+#             */
/*   Updated: 2023/12/04 21:03:18 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_base_len(char *base)
{
	int	i;

	i = 0;
	if (base[0] == '\0')
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	if (i == 1)
		return (0);
	return (i);
}

int	ft_test_base(int len, char *base)
{
	int	x;
	int	y;

	x = 0;
	y = 1;
	while (x < len - 1)
	{
		while (y < len)
		{
			if (base[x] == base[y])
				return (0);
			else
				y++;
		}
		x++;
		y = x + 1;
	}
	return (1);
}
