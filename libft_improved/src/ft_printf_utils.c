/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 04:50:32 by saperrie          #+#    #+#             */
/*   Updated: 2024/01/20 03:37:13 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ui	put_p(void *ptr, int *count, const char *format)
{
	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	else
	{
		write(1, "0x", 2);
		return ((u_putnbr_base((t_ul)ptr, count, format)) + 2);
	}
}

int	put_s(char *str)
{
	if (str == NULL)
		return (write(1, "(null)", 6));
	else
		return (putstr_sz(str));
}

int	ft_percent(const char *format, va_list args)
{
	int		count;
	char	*base_10;

	base_10 = "0123456789";
	count = 0;
	if (*format == 'c')
		return (putchar_sz(va_arg(args, int)));
	else if (*format == 's')
		return (put_s((void *)va_arg(args, char *)));
	else if (*format == 'p')
		return (put_p((void *)va_arg(args, void *), &count, format));
	else if (*format == 'd' || *format == 'i')
		return (putnbr_base(va_arg(args, int), &count, base_10));
	else if (*format == 'u')
		return (u_putnbr_base(va_arg(args, t_ui), &count, format));
	else if (*format == 'x')
		return (u_putnbr_base(va_arg(args, t_ui), &count, format));
	else if (*format == 'X')
		return (u_putnbr_base(va_arg(args, t_ui), &count, format));
	else if (*format == '%')
		return (write(1, "%", 1));
	else
		return (0);
}
