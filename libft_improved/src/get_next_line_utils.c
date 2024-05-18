/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:27:44 by saperrie          #+#    #+#             */
/*   Updated: 2024/01/20 03:51:42 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static size_t	ft_strlen(char const *str)
// {
// 	size_t	length;

// 	length = 0;
// 	while (str[length])
// 		length++;
// 	return (length);
// }

// static char	*ft_calloc(size_t nmemb, size_t size)
// {
// 	char	*mem_alloc;
// 	size_t	index;

// 	if (nmemb == 0 || size == 0)
// 		return (NULL);
// 	if (nmemb > SIZE_MAX / size)
// 		return (NULL);
// 	mem_alloc = malloc(nmemb * size);
// 	if (!mem_alloc)
// 		return (NULL);
// 	index = -1;
// 	while (++index < nmemb * size)
// 		mem_alloc[index] = 0;
// 	return (mem_alloc);
// }

char	*ft_strncat(char *dest, char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[j])
		j++;
	while (i < n && src[i] != '\0')
	{
		dest[j + i] = src[i];
		i++;
	}
	dest[j + i] = '\0';
	j = 0;
	while (src[i])
		src[j++] = src[i++];
	while (src[j])
		src[j++] = '\0';
	return (dest);
}

size_t	ft_find_chr(char *s, char c)
{
	size_t	count;

	count = 0;
	if (!s || !s[0])
		return (0);
	while (s[count])
	{
		if (s[count] == c)
			return (count + 1);
		count++;
	}
	if (c == '\0')
		return (count);
	return (0);
}

char	*ft_realloc(char *line, size_t buf_size)
{
	char	*new_line;

	if (!line)
		new_line = ft_calloc((buf_size + 1), sizeof(char));
	else
	{
		new_line = ft_calloc((buf_size + ft_strlen(line) + 1), sizeof(char));
		if (!new_line)
			return (free(line), NULL);
		new_line = ft_strncat(new_line, line, ft_strlen(line));
	}
	free(line);
	return (new_line);
}
