/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:10:09 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/23 00:51:52 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../I_header/minishell.h"

bool	is_arg_format(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '\'' || c == '"')
		return (true);
	return (false);
}

char	*quote_mode(char *str, char quote, size_t *length)
{
	while (*str != quote && *str)
		*length += 1;
	return (str + (*length));
}

bool	is_quote(char c, char quote)
{
	if (c == quote)
		return (true);
	return (false);
}

const char	*skip_quote_content(const char *str, char quote, size_t *length)
{
	str += 1;
	*length += 1;
	while (*str && !is_quote(*str, quote))
	{
		str++;
		*length += 1;
	}
	*length += 1;
	return (str + 1);
}
