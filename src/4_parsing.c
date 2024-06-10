/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:55:40 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/10 21:14:02 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static bool	tag_arg(t_line *line)
{
	char	**cpy;
	size_t	tablen;

	cpy = line->pipe->arg;
	tablen = ft_tablen(cpy);
	line->pipe->arg = ft_calloc(tablen + 1 + 1, sizeof(char *));
	if (!line->pipe->arg)
		return (false);
	ft_memcpy(line->pipe->arg, cpy, tablen * sizeof(char *));
	line->pipe->arg[tablen] = line->argv->node;
	printf("\t     ARG: %s\n", line->argv->node);
	return (true);
}

bool	handle_redir(t_line *line)
{
	char	operator;

	operator = is_redirection_operator((line->argv->node));
	if (operator == IN_REDIR && process_redir(line, IN_REDIR))
		printf("\t    type: <\n\n");
	else if (operator == OUT_REDIR && process_redir(line, OUT_REDIR))
		printf("\t    type: >\n\n");
	else if (operator == APPEND && process_redir(line, APPEND))
		printf("\t    type: >>\n\n");
	else if (operator == HEREDOC && process_redir(line, HEREDOC))
		printf("\t    type: <<\n\n");
	else
		return (0);
	return (1);
}

static	bool	handle_pipe(t_line *line)
{
	line->pipe->next = ft_calloc(1, sizeof(t_pipe));
	if (!line->pipe->next)
		return (false);
	line->pipe->next->prev = line->pipe;
	line->pipe = line->pipe->next;
	printf("PIPE\n");
	return (true);
}

static	bool	tag_tokens(t_line *line)
{
	line->pipe = ft_calloc(1, sizeof(t_pipe));
	if (!line->pipe)
		return (false);
	line->pipe->prev = NULL;
	line->pipe->next = NULL;
	while (line->argv)
	{
		if (*line->argv->node == '|')
		{
			if (!handle_pipe(line))
				return (false);
		}
		else if (is_redirection_operator(line->argv->node))
		{
			if (!handle_redir(line))
				return (false);
		}
		else
			if (!tag_arg(line))
				return (false);
		line->argv = line->argv->next;
	}
	return (true);
	// free_t_line_argv();
}

// FIXME include pipes
bool	parse(t_line *line)
{
	line->argv = line->argv_head;
	if (!clean_surrounding_quotes(line))
		return (printf("clean_quotes_failed\n"), false);
	line->argv = line->argv_head;
	if (!tag_tokens(line))
		return (false);
	return (true);
}
