/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 01:11:15 by saperrie          #+#    #+#             */
/*   Updated: 2023/11/21 00:10:17 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_int(int n)
{
	int	char_count;

	char_count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		char_count++;
	}
	while (n > 0)
	{
		n /= 10;
		char_count++;
	}
	return (char_count);
}

static char	*ft_zero(char *str)
{
	str[0] = '0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		index;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	index = ft_count_int(n);
	str = (char *)malloc(sizeof(char) * (index + 1));
	if (!str)
		return (NULL);
	str[index--] = '\0';
	if (n == 0)
		return (ft_zero(str));
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		str[index] = (n % 10) + 48;
		n /= 10;
		index--;
	}
	return (str);
}
