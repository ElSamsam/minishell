/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:11:19 by saperrie          #+#    #+#             */
/*   Updated: 2023/11/21 18:55:01 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const *set, char c)
{
	int	index;

	index = -1;
	while (set[++index])
	{
		if (c == set[index])
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	finish;
	size_t	trim_len;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && is_set(set, s1[start]) == 1)
		start++;
	finish = ft_strlen(s1);
	while (is_set(set, s1[finish - 1]) == 1)
		finish--;
	trim_len = finish - start;
	return (ft_substr(s1, start, trim_len));
}
