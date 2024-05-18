/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 00:39:00 by saperrie          #+#    #+#             */
/*   Updated: 2023/11/25 13:57:31 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dst, char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = -1;
	while (dst[i])
		i++;
	while (src[++j])
		dst[i + j] = src[j];
	dst[i + j] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	big_len;
	char	*big_s;

	if (!s1 || !s2)
		return (0);
	big_len = ft_strlen(s1) + ft_strlen(s2);
	big_s = malloc((sizeof (char) * big_len) + 1);
	if (!big_s)
		return (NULL);
	big_s[0] = '\0';
	ft_strcat(big_s, (char *)s1);
	ft_strcat(big_s, (char *)s2);
	return (big_s);
}
