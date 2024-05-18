/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:40:11 by saperrie          #+#    #+#             */
/*   Updated: 2024/01/20 03:36:09 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		length;
	int		error;

	if (!format)
		return (-1);
	va_start(args, format);
	length = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			error = ft_percent(format++, args);
			if (error == -1)
				return (error);
			length += error;
		}
		else
			length += write(1, format++, 1);
	}
	va_end(args);
	return (length);
}
