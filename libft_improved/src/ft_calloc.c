/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:15:16 by saperrie          #+#    #+#             */
/*   Updated: 2023/11/21 20:06:54 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem_alloc;
	size_t	index;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	mem_alloc = malloc(nmemb * size);
	if (mem_alloc == NULL)
		return (0);
	index = -1;
	while (++index < nmemb * size)
		((char *)mem_alloc)[index] = 0;
	return (mem_alloc);
}
