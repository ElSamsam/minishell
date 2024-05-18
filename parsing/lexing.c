/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:08:18 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/17 16:29:08 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static short	is_white_space(char c)
{
	if (c == '\f' || c == '\n' || c == '\t' 
		|| c == '\v' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

static void	skip_white_spaces(char **input)
{
	if (!*input || !**input)
		return ;
	while (is_white_space(**input))
		(*input)++;
}

static size_t	len_to_next_white_space(char *input)
{
	size_t	len;

	len = 0;
	while (*input && is_white_space(*input))
	{
		input++;
		len++;
	}
	return (len);
}

// static short	make_tokens(char *input, t_line *line, int i)
// {
// 	size_t	len;

// 	skip_white_spaces(&input);
// 	while (*input && !is_white_space(*input))
// 	{
// 		len = len_to_next_white_space(input);
// 		line->cmd->arr[i++] = ft_substr(input, 0, len);
// 	}
// }

void	lex(char *input, t_line *line)
{
	// make_tokens(input, line, 0);
	// clean_parasite_quotes(input);
	// mark_dollar_for_interp(input);
	// split_bis();
}