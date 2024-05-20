/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 03:27:40 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/21 01:06:06 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I_header/minishell.h"

// =======================TOKENS UTILS==========================
static	bool	is_arg_format(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

static char	*fill_argv_loop(const char *input, t_line *line, size_t token_len)
{
	line->argv = malloc(sizeof(t_argv *));
	if (!line->argv)
		return (NULL);
	line->argv->av = ft_substr((const char *)input, 0, token_len);
	if (!*(line->argv->av))
		return (NULL);
	printf("AV: %c\n", *(line->argv->av));
	line->argv->next = NULL;
	line->argv = line->argv->next;
	return ((char *)input);
}
// =======================TOKENS UTILS==========================

static	char	*tokenise_arg_and_iterate_through(char *input, t_line *line)
{
	size_t	token_length;
	char	*input_cpy;

	token_length = 0;
	if (!*input || !input)
		return (NULL);
	input_cpy = input;
	while (is_arg_format(*input_cpy))
	{
		token_length += 1;
		input_cpy += 1;
	}
	input = fill_argv_loop(input, line, token_length);
	if (!*input || !input)
		return (NULL);
	return (input_cpy);
}

bool	make_tokens(char *input, t_line *line)
{
	size_t	len;
	char	cmd;

	cmd = 0;
	line->argc = 0;
	while (*input)
	{
		skip_white_spaces((const char **)&input);
		if (!*input)
			return (true);
		if (is_arg_format(*input) && !cmd)
		{
			input = tokenise_arg_and_iterate_through(input, line);
			if (!*input)
				return (true);
			cmd = 1;
			line->argc = 1;
		}
		else if (is_arg_format(*input))
			input = tokenise_arg_and_iterate_through(input, line);
		// else if (is_redir(*input))
		// 	tokenise_redir_and_fd(&input, &line);
		else
			input += 1;
	}
	return (true);
}
