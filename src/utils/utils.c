/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:10:09 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/20 16:42:02 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_white_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

size_t	skip_white_spaces(char **input)
{
	size_t	wspace_len;

	wspace_len = 0;
	if (!*input || !**input || !input)
		return (0);
	while (is_white_space(**input))
	{
		wspace_len += 1;
		(*input)++;
	}
	return (wspace_len);
}

bool	is_quote(char c, char quote)
{
	if (c == quote)
		return (true);
	return (false);
}

char	*skip_quote_content(char *str, char quote)
{
	if (*str == '\'' || *str == '"')
		str += 1;
	while (*str && (!is_quote(*str, quote) || *str == '|'))
	{
		if (*str == '|')
			*str *= -1;
		if (quote == '\'' && *str == '$')
			*str *= -1;
		str++;
	}
	if (*str == '\'' || *str == '"')
		return (str + 1);
	return (str);
}

size_t	count_argv_nodes(t_line *line)
{
	size_t	node_count;

	node_count = 0;
	while (line->argv && *line->argv->node != '|')
	{
		node_count += 1;
		line->argv = line->argv->next;
	}
	line->argv = line->argv_head;
	return (node_count);
}
