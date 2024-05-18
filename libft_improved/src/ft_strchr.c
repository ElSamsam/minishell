/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:36:28 by saperrie          #+#    #+#             */
/*   Updated: 2023/11/21 18:47:49 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char const *s, int c)
{
	int	count;

	count = 0;
	if ((char) c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[count])
	{
		if (s[count] == (char) c)
			return ((char *)&s[count]);
		count++;
	}
	return (NULL);
}
