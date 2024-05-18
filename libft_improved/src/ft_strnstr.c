/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:23:41 by saperrie          #+#    #+#             */
/*   Updated: 2024/03/04 19:33:53 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *big, char const *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	mem_i;

	i = -1;
	j = -1;
	if (!(little[++j]))
		return ((char *)big);
	while ((big[++i] && i <= len))
	{
		if (big[i] == little[0])
		{
			mem_i = i;
			while (little[j] == big[i] && i < len)
			{
				if (little[j + 1] == '\0')
					return ((char *)&big[mem_i]);
				i++;
				j++;
			}
			i = mem_i;
		}
		j = 0;
	}
	return (NULL);
}
