/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:19:28 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/17 18:10:04 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// =================================== QUOTES =================================
static char	*find_matching_quote(char *str, char quote)
{
	while (*str)
	{
		if (*str == quote)
			return (str);
		str++;
	}
	return (NULL);
}

static short	even_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			str = find_matching_quote(++str, '\'');
			if (!str)
				return (0);
		}
		else if (*str == '"')
		{
			str = find_matching_quote(++str, '"');
			if (!str)
				return (0);
		}
		str++;
	}
	return (1);
}
// =================================== QUOTES =================================

// =================================== REDIR ==================================
static	short	redir_family_incr(char **str)
{
	if (**str == '<' && **str + 1 == '<')
		return ((*str + 2), 1);
	else if (**str == '>' && **str + 1 == '>')
		return ((*str + 2), 1);
	else if (**str == '<')
		return ((*str + 1), 1);
	else if (**str == '>')
		return ((*str + 1), 1);
	return (0);
}

static	short	is_redir(char *str)
{
	if (*str == '<' && *str + 1 == '<')
		return (4);
	else if (*str == '>' && *str + 1 == '>')
		return (3);
	else if (*str == '>')
		return (2);
	else if (*str == '<')
		return (1);
	return (0);
}

static	short	redir_into_redir(char *str)
{
	while (*str)
	{
		if (redir_family_incr(&str))
		{
			if (is_redir(str))
				return (0);
			
		}
	}
}
// =================================== REDIR ==================================

short	clean_input(char *input)
{
	if (!even_quotes(input))
		return (printf("parsing error: missing quote\n"), 0);
	if (!redir_into_redir(input))
		return (printf("VI2MERD"), 0);
	return (1);
}