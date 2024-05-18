/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:42:45 by saperrie          #+#    #+#             */
/*   Updated: 2023/11/21 18:36:11 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			count;
	unsigned char	*z1;
	unsigned char	*z2;

	if (!n)
		return (0);
	count = 0;
	z1 = (unsigned char *)s1;
	z2 = (unsigned char *)s2;
	while (count + 1 < n && z1[count] == z2[count])
		count++;
	return (z1[count] - z2[count]);
}
