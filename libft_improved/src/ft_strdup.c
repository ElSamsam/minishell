/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:35:22 by saperrie          #+#    #+#             */
/*   Updated: 2023/11/21 18:49:43 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *s)
{
	char	*new_s;
	size_t	s_len;

	s_len = ft_strlen(s);
	new_s = malloc(sizeof (char) * s_len + 1);
	if (!new_s)
		return (NULL);
	new_s = ft_memcpy((char *)new_s, (char *)s, s_len);
	new_s[s_len] = '\0';
	return (new_s);
}
