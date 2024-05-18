/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:58:40 by saperrie          #+#    #+#             */
/*   Updated: 2023/11/17 21:06:36 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **big_tab)
{
	size_t	index;

	index = 0;
	while (big_tab[index])
		free(big_tab[index++]);
	free(big_tab);
	return (NULL);
}

static char	**ft_alloc(char const *s, char c)
{
	size_t	word_count;
	size_t	index;

	word_count = 0;
	index = 0;
	while (s[index])
	{
		if (s[index] != c && (index == 0 || s[index - 1] == c))
			word_count++;
		index++;
	}
	return ((char **)malloc(sizeof(char *) * (word_count + 1)));
}

char	**ft_split(char const *s, char c)
{
	char	**big_tab;
	char	*separator;
	size_t	word_count;

	if (!s)
		return (NULL);
	big_tab = ft_alloc(s, c);
	if (!big_tab)
		return (NULL);
	separator = (char *)s - 1;
	word_count = 0;
	while (s[0])
	{
		if (s[0] == c)
			separator = (char *)s;
		else if (s[1] == c || s[1] == '\0')
		{
			big_tab[word_count] = ft_substr(separator + 1, 0, s - separator);
			if (!big_tab[word_count++])
				return (ft_free(big_tab));
		}
		s++;
	}
	big_tab[word_count] = 0;
	return (big_tab);
}
