/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   C_parse_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 00:07:21 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/21 16:40:33 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../I_header/minishell.h"

// static char	*turn_quote_content_negative(char *str)
// {
// 	;
// }

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

bool	quotes(char *str)
{
	if (!even_quotes(str))
		return (printf("minishell: parsing error: missing quote\n"), false);
	return (true);
}
