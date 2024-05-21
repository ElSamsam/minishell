/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_lexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:08:18 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/22 01:18:40 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../I_header/minishell.h"

static char	*fill_argv(const char *input, t_line *line, size_t token_len)
{
	bool	argv;

	argv = false;
	if (!argv)
	{
		line = make_t_line_argv_node(input, token_len, line);
		argv = true;
	printf("AV%i: %s\n", line->argc, line->argv->av);
	}
	// line = make_t_line_argv_node(input, token_len, line);
	if (!line || !line->argv)
		return (NULL);
	return ((char *)input);
}

static	char	*tokenise_arg_and_iterate_through(char *input, t_line *line)
{
	size_t	token_length;
	char	*ptr_cpy;

	token_length = 0;
	ptr_cpy = input;
	while (*ptr_cpy && !is_white_space(*ptr_cpy))
	{
		if (*ptr_cpy == '\'')
			ptr_cpy = skip_quote_content(ptr_cpy, '\'', &token_length);
		else if (*ptr_cpy == '"')
			ptr_cpy = skip_quote_content(ptr_cpy, '"', &token_length);
		else
		{
			token_length += 1;
			ptr_cpy++;
		}
	}
	if (!*input)
		return (NULL);
	input = fill_argv(input, line, token_length);
	if (!input)
		return (NULL);
	return (ptr_cpy);
}

static bool	make_tokens(char *input, t_line *line)
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
		}
		// else if (is_redir_format(*input))
		// 	tokenise_redir_and_fd(&input, &line);
		else
			input += 1;
	}
	return (true);
}

bool	lex(char *input, t_line *line)
{
	if (!make_tokens(input, line))
		return (printf("BAD_TOKEN\n", false));
	return (true);
}
