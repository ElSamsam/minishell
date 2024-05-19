/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_clean_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:19:28 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/19 01:50:35 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../1_header/minishell.h"

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

static bool	even_quotes(char *str)
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
// =================================== QUOTES =================================

// =================================== REDIR ==================================
bool	skip_redirection_operator(const char **str)
{
	if (**str == '<' && **str + 1 == '<')
		return ((*str) + 2, true);
	else if (**str == '>' && **str + 1 == '>')
		return ((*str) + 2, true);
	else if (**str == '<')
		return ((*str) + 1, true);
	else if (**str == '>')
		return ((*str) + 1, true);
	return (false);
}

static short	is_redirection_operator(const char *str)
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

static	bool	redir_into_redir(const char *str)
{
	while (*str)
	{
		if (skip_redirection_operator(&str))
		{
			skip_white_spaces(&str);
			if (is_redirection_operator(str))
				return (false);
		}
		else
			str++;
	}
	if (!*str)
		return (false);
	return (true);
}

short	count_redirection_operators(const char *str)
{
	short	redir_count;

	redir_count = 0;
	while (*str)
	{
		if (skip_redirection_operator(&str))
			redir_count++;
		else
			str++;
	}
	return (redir_count);
}
// =================================== REDIR ==================================

// =================================== SPACE_OUT ==============================

static char	*ft_strncpy(char *dest, char *src, size_t length)
{
	size_t	i;

	i = 0;
	while (src[i] && i < length)
	{
		dest[i] = src[i];
		i++;
	}
	// while (i < length)
	// {
	// 	dest[i] = '\0';
	// 	i++;
	// }
	return (dest);
}

static char	*offset_str_one_to_the_right(char **str)
{
	size_t i;

	i = 0;
	while (*str[i])
		i++;
	while (i > 0)
	{
		*str[i] = *str[i - 1];
		i--;
	}
	return (*str);
}

static char	*put_space_before_and_after_redir_operators(char *str)
{
	offset_str_one_to_the_right(&str);
	str[0] = ' ';
	while (*str)
	{
		if (skip_redirection_operator((const char **)&str))
			*str = ' ';
		else
			str++;
	}
	offset_str_one_to_the_right(&str);
	return (str);
}

static char *ft_realloc_plus_redir_count_times_two(char *str, short redir_count)
{
	char	*new_str;
	size_t	new_len;

	new_len = ft_strlen(str) + (redir_count * 2);
	new_str = ft_calloc(sizeof(char), new_len + 1);
	if (!new_str)
		return (NULL);
	new_str = ft_strncpy(new_str, str, new_len);
	return (new_str);
}

static char	*space_out(char *str)
{
	short	redir_count;

	redir_count = count_redirection_operators(str);
	if (!redir_count)
		return (str);
	str = ft_realloc_plus_redir_count_times_two(str, redir_count);
	if (!str)
		return (NULL);
	return (put_space_before_and_after_redir_operators(str));
}
// =================================== SPACE_OUT ==============================

bool	clean_input(char *str)
{
	skip_white_spaces((const char **)&str);
	str = space_out(str);
	if (!str)
		return (false);
	if (!even_quotes(str))
		return (printf("parsing error: missing quote\n"), false);
	if (!redir_into_redir(str))
		return (printf("VI2MERD"), false);
	return (true);
}