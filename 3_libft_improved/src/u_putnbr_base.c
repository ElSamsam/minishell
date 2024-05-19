/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_putnbr_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:28:06 by saperrie          #+#    #+#             */
/*   Updated: 2024/03/17 23:43:57 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*which_base(const char *format)
{
	if (*format == 'x' || *format == 'p')
		return ("0123456789abcdef");
	else if (*format == 'X')
		return ("0123456789ABCDEF");
	else
		return ("0123456789");
}

int	u_putnbr_base(unsigned long nbr, int *count, const char *format)
{
	unsigned long	base_len;
	int				error;
	char			*base;

	base = 0;
	if (*format == 'x' || *format == 'X' || *format == 'u' || *format == 'p')
		base = which_base(format);
	if (!base)
		return (0);
	base_len = ft_strlen(base);
	if (base_len == 0)
		return (0);
	if (nbr < base_len)
	{
		error = putchar_sz(base[nbr]);
		if (error == -1)
			return (error);
		*count += error;
	}
	if (nbr >= base_len)
	{
		u_putnbr_base(nbr / base_len, count, format);
		u_putnbr_base(nbr % base_len, count, format);
	}
	return (*count);
}
