/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 00:07:21 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/23 06:26:31 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../I_header/minishell.h"
#include <stdbool.h>
#include <stdio.h>

// static char	*turn_quote_content_negative(char *str)
// {
// 	;
// }

const char	*find_matching_quote(const char *str, char quote)
{
	while (*str)
	{
		if (*str == quote)
			return (str);
		str++;
	}
	return (NULL);
}

bool	even_quotes(const char *str)
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

// static bool	terrible_input(const char *str)
// {
// 	while (*str && (*str == ' ' || *str == '\'' || *str == '"' || is_redirection_operator(str)))
// 		str += 1;
// 	if (!*str)
// 		return (true);
// 	return (false);
// }

bool	quotes(const char *str)
{
	if (!even_quotes(str))
		return (printf("minishell: parsing error: missing quote\n"), (false));
	// if (terrible_input(str))
	// 	return (printf("nice try :)"), (false));
	return (true);
}
