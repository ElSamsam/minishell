/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:15:50 by saperrie          #+#    #+#             */
/*   Updated: 2023/11/21 18:54:19 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int c)
{
	int	count;

	count = ft_strlen(s) - 1;
	if ((char) c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (count >= 0)
	{
		if (s[count] == (char) c)
			return ((char *)&s[count]);
		count--;
	}
	return (NULL);
}
