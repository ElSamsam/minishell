/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:01 by saperrie          #+#    #+#             */
/*   Updated: 2023/11/21 20:12:16 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	size_t			count;
	unsigned char	*z1;
	unsigned char	*z2;

	count = 0;
	z1 = (unsigned char *)s1;
	z2 = (unsigned char *)s2;
	while ((z1[count] || z2[count]) && count < n)
	{
		if (z1[count] != z2[count])
			return (z1[count] - z2[count]);
		count++;
	}
	return (0);
}
