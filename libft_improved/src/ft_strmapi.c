/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:27:31 by saperrie          #+#    #+#             */
/*   Updated: 2023/11/17 18:55:30 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	index;
	char	*new_s;

	index = -1;
	new_s = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_s)
		return (NULL);
	while (s[++index])
		new_s[index] = f(index, s[index]);
	new_s[index] = '\0';
	return (new_s);
}
