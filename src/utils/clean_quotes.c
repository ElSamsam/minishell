/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 00:07:21 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/20 16:44:13 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	memcpy_skips_quotes(char *str, int *dst, int *src)
{
	char	quote;

	quote = str[(*src)++];
	while (str[*src] != quote && str[*src])
	{
	// printf("(%i) <- (%i) [%x]`%c'\n", *dst, *src, str[*src], str[*src]);
		str[*dst] = str[*src];
		*dst += 1;
		*src += 1;
	}
	if (!str[(*src)])
		return ;
	(*src) += 1;
}

bool	clean_surrounding_quotes(t_line *line)
{
	int	dst;
	int	src;

	while (line->argv)
	{
		dst = 0;
		src = 0;
		while (line->argv->node[dst] && line->argv->node)
		{
			if (!line->argv->node[src])
				line->argv->node[dst] = '\0';
			else if (line->argv->node[src] == '"' \
			|| line->argv->node[src] == '\'')
				memcpy_skips_quotes(line->argv->node, &dst, &src);
			else
				line->argv->node[dst++] = line->argv->node[src++];
		}
		// printf("\tclean%i: %s\n", line->argv->node_index, line->argv->node);
		line->argv = line->argv->next;
	}
	return (true);
}

char	*find_matching_quote(char *str, char quote)
{
	while (*str)
	{
		if (*str == quote)
			return (str);
		str++;
	}
	return (NULL);
}

bool	even_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			str = find_matching_quote(++str, '\'');
			if (!str)
				return (false);
		}
		else if (*str == '"')
		{
			str = find_matching_quote(++str, '"');
			if (!str)
				return (false);
		}
		str++;
	}
	return (true);
}
