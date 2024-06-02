/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:03:47 by saperrie          #+#    #+#             */
/*   Updated: 2023/11/15 23:33:16 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	index;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!s || start >= s_len)
		return (ft_calloc(1, 1));
	if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc(sizeof(char) * len + 1);
	if (!substr)
		return (0);
	index = -1;
	while (++index < len)
		substr[index] = s[start + index];
	substr[index] = '\0';
	return (substr);
}
