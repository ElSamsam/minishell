/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:05:11 by saperrie          #+#    #+#             */
/*   Updated: 2023/11/21 18:50:49 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char const *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	index;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	index = 0;
	if (size < len_dst)
		return (size + len_src);
	while (src[index] != '\0' && (len_dst + index + 1) < size)
	{
		dst[len_dst + index] = src[index];
		index++;
	}
	dst[len_dst + index] = '\0';
	return (len_dst + len_src);
}
