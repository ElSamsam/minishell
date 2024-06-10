/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_lexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:08:18 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/09 22:30:52 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

// TODO turn this function into two
t_line	*make_argv_node(char *input, size_t len, t_line *line)
{
	t_argv	*next_node;

	if (!line->argc++)
	{
		line->argv = malloc(sizeof(t_argv));
		if (!line->argv)
			return (NULL);
		line->argv_head = line->argv;
		line->argv->prev = NULL;
		line->argv->next = NULL;
		line->argv->node_index = line->argc;
		line->argv->node = ft_substr(input, 0, len);
		if (!line->argv->node)
			return (NULL);
	}
	else
	{
		next_node = malloc(sizeof(t_argv));
		if (!next_node)
			return (NULL);
		next_node->prev = line->argv;
		line->argv->next = next_node;
		line->argv = next_node;
		line->argv->next = NULL;
		line->argv->node_index = line->argc;
		line->argv->node = ft_substr(input, 0, len);
		if (!line->argv->node)
			return (NULL);
	}
	return (line);
}

static char	*fill_argv(char *input, t_line *line, size_t token_len)
{
	line = make_argv_node(input, token_len, line);
	if (!line || !line->argv)
		return (NULL);
	printf("\tAV%i: %s\n", line->argv->node_index, line->argv->node);
	return (input);
}

static char	*tokenise(char *ptr, t_line *line)
{
	char	*cpy;

	// skip_white_spaces(&ptr);
	cpy = ptr;
	if (skip_redirection_operator(&cpy))
		skip_white_spaces(&cpy);
	while (*cpy && !is_white_space(*cpy) && !is_redirection_operator(cpy) \
		&& *cpy != '|')
	{
		if (*cpy == '\'')
			cpy = skip_quote_content(cpy, '\'');
		else if (*cpy == '"')
			cpy = skip_quote_content(cpy, '"');
		else
			cpy += 1;
	}
	if (is_redirection_operator(cpy))
		return (printf("redir into %c\n", *cpy), NULL);
	ptr = fill_argv(ptr, line, cpy - ptr);
	if (!ptr)
		return (NULL);
	return (cpy);
}

static	char	*which_token(char *input, t_line *line)
{
	char	*ptr;

	ptr = input;
	if (*ptr == '|')
	{
		ptr = fill_argv(input, line, 1);
		ptr += 1;
	}
	else
		ptr = tokenise(ptr, line);
	if (!ptr)
		return (NULL);
	return (ptr);
}

static bool	make_tokens(char *input, t_line *line)
{
	line->argc = 0;
	while (*input)
	{
		skip_white_spaces(&input);
		if (!*input)
			return (true);
		input = which_token(input, line);
		if (!input)
			return (false);
	}
	return (true);
}

bool	lex(char *input, t_line *line)
{
	if (!make_tokens(input, line))
		return (printf("BAD_TOKEN\n"), false);
	return (true);
}

	// char	*ptr_cpy;

	// ptr_cpy = input;
	// if (skip_redirection_operator(&ptr_cpy))
	// 	skip_white_spaces(&ptr_cpy);
	// if (is_redirection_operator(ptr_cpy)/* || *ptr_cpy == '|'*/)
	// 	return (printf("syntax error near unexpected token `%c'\n", *ptr_cpy), \
	// 		NULL);
	// while (*ptr_cpy && !is_white_space(*ptr_cpy) \
	// 	&& !is_redirection_operator(ptr_cpy) && *ptr_cpy != '|')
	// {
	// 	// if (*ptr_cpy == '|')
	// 	// {
	// 	// 	ptr_cpy += 1;
	// 	// 	break ;
	// 	// }
	// 	if (*ptr_cpy == '\'')
	// 		ptr_cpy = skip_quote_content(ptr_cpy, '\'');
	// 	else if (*ptr_cpy == '"')
	// 		ptr_cpy = skip_quote_content(ptr_cpy, '"');
	// 	else
	// 		ptr_cpy += 1;
	// }
	// if (!*input)
	// 	return (NULL);
	// input = fill_argv(input, line, ptr_cpy - input);
	// if (*ptr_cpy == '|') // TODO INCLUDE PIPE->NEXT WHEN NEEDED
	// {
	// 	// printf("%i", line->argv->node_index);
	// 	// if (is_redirection_operator(line->argv->node))
	// 	// 	return (printf("parsing error\n"), NULL);
	// 	// input = fill_argv(input, line, ptr_cpy - input);
	// 	input += (ptr_cpy - input);
	// 	ptr_cpy += 1;
	// 	line->pipe = line->pipe->next;
	// 	printf("NEW PIPE\n");
	// 	input = fill_argv(input, line, ptr_cpy - input);
	// }
	// if (!input)
	// 	return (NULL);
	// return (ptr_cpy);