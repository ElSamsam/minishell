/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 03:27:40 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/21 19:21:19 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I_header/minishell.h"
#include <stdbool.h>
#include <stdio.h>

// =======================TOKENS UTILS==========================
static	bool	is_arg_format(char c)
{
	if (ft_isalnum(c) || c == '_' || is_valid_fd_name(c)
		|| c == '\'' || c == '"')
		return (true);
	return (false);
}

static	char	*quote_mode(char *str, char quote, size_t *length)
{
	while (*str != quote && *str)
		*length += 1;
	return (str + (*length));
}

static	bool	is_quote(char c, char quote)
{
	if (c == quote)
		return (true);
	return (false);
}

static char	*fill_argv(const char *input, t_line *line, size_t token_len)
{
	line->argv = malloc(sizeof(t_argv));
	if (!line->argv)
		return (NULL);
	line->argv->av = ft_substr((const char *)input, 0, token_len);
	if (!*(line->argv->av))
		return (NULL);
	if (*input == '\'' || *input == '"')
		printf("AV%i: %s\n", ++line->argc, line->argv->av);
	else
		printf("AV%i: %s\n", ++line->argc, line->argv->av);
	line->argv->next = NULL;
	line->argv = line->argv->next;
	return ((char *)input);
}

static char	*skip_quote_content(char *str, char quote, size_t *length)
{
	*length += 1;
	while (*str && !is_quote(*str, quote))
	{
		str++;
		*length += 1;
	}
	*length += 1;
	return (str + 1);
}
// =======================TOKENS UTILS==========================

static	char	*tokenise_arg_and_iterate_through(char *input, t_line *line)
{
	size_t	token_length;
	char	*ptr_cpy;

	token_length = 0;
	if (!*input || !input)
		return (NULL);
	ptr_cpy = input;
	while (*ptr_cpy && !is_white_space(*ptr_cpy))
	{
		if (*ptr_cpy == '\'')
		{
			ptr_cpy = skip_quote_content(++ptr_cpy, '\'', &token_length);
		}
		else if (*ptr_cpy == '"')
			ptr_cpy = skip_quote_content(++ptr_cpy, '"', &token_length);
		else
		{
			token_length += 1;
			ptr_cpy++;
		}
	}
	if (!*input || !input)
		return (NULL);
	input = fill_argv(input, line, token_length);
	if (!*input || !input)
		return (NULL);
	return (ptr_cpy);
}

bool	make_tokens(char *input, t_line *line)
{
	while (*input)
	{
		skip_white_spaces((const char **)&input);
		if (is_arg_format(*input) && *input)
		{
			input = tokenise_arg_and_iterate_through(input, line);
			if (!input)
				return (false);
			if (!*input)
				return (true);
			// line->argc += 1;
		}
		else
			input += 1;
		// else if (is_redir(*input))
		// 	tokenise_redir_and_fd(&input, &line);
	}
	return (true);
}

		// if (is_quote(*ptr_cpy, '\'') && s_quote == 1)
		// 	s_quote *= -1;
		// else if (is_quote(*ptr_cpy, '"') && d_quote == 1)
		// 	d_quote *= -1;
		// else if (*ptr_cpy == '\'' && s_quote == -1 && d_quote == -1)
		// {
		// 	s_quote *= -1;
		// 	ptr_cpy = quote_mode(ptr_cpy++, '\'', &token_length);
		// }
		// else if (*ptr_cpy == '"' && d_quote == -1 && d_quote == -1)
		// {
		// 	d_quote *= -1;
		// 	ptr_cpy = quote_mode(ptr_cpy++, '"', &token_length);
		// }
		// else