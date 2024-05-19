/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:28:06 by saperrie          #+#    #+#             */
/*   Updated: 2024/01/20 04:05:04 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	putnbr_base(int nbr, int *count, char *base_10)
{
	int		error;

	if (nbr == -2147483648)
		return (write(1, "-2147483648", 11));
	if (nbr < 0)
	{
		error = putchar_sz('-');
		if (error == -1)
			return (error);
		*count += error;
		nbr *= -1;
	}
	if (nbr < 10)
	{
		error = putchar_sz(base_10[nbr]);
		if (error == -1)
			return (error);
		*count += error;
	}
	if (nbr >= 10)
	{
		putnbr_base(nbr / 10, count, base_10);
		putnbr_base(nbr % 10, count, base_10);
	}
	return (*count);
}
