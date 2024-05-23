/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_lexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:08:18 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/23 02:30:56 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../I_header/minishell.h"

static char	*fill_argv(const char *input, t_line *line, size_t token_len)
{
	line = make_t_line_argv_node(input, token_len, line);
	if (!line || !line->argv)
		return (NULL);
	printf("\tAV%i: %s\n", line->argv->node_index, line->argv->av);
	return ((char *)input);
}

static	const char	*tokenise_arg(const char *input, t_line *line)
{
	size_t		token_length;
	const char	*ptr_cpy;

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
			ptr_cpy += 1;
		}
	}
	if (!*input)
		return (NULL);
	input = fill_argv(input, line, token_length);
	if (!input)
		return (NULL);
	return (ptr_cpy);
}

static bool	make_tokens(const char *input, t_line *line)
{
	line->argc = 0;
	line->token_index = 0;
	while (*input)
	{
		skip_white_spaces(&input);
		if (!*input)
			return (true);
		input = tokenise_arg(input, line);
		if (!input)
			return (false);
		// else if (is_redir_format(*input))
		// 	tokenise_redir_and_fd(&input, &line);
	}
	return (true);
}

bool	lex(const char *input, t_line *line)
{
	if (!make_tokens(input, line))
		return (printf("BAD_TOKEN\n", false));
	return (true);
}
