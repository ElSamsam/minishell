/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:10:09 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/03 06:25:02 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_white_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

size_t	skip_white_spaces(const char **input)
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

const char	*skip_quote_content(const char *str, char quote)
{
	if (*str == '\'' || *str == '"')
		str += 1;
	while (*str && !is_quote(*str, quote))
		str++;
	if (*str == '\'' || *str == '"')
		return (str + 1);
	return (str);
}
