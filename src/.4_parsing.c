/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:55:40 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/09 22:41:48 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

//  FIXME this workin but 5 functions
static char	extract_node(t_line *line)
{
	if (!line->argv->prev && !line->argv->next)
	{
		// free(line->argv->node);
		// free(line->argv);
		// line->argv = NULL;
		return (3);
	}
	else if (!line->argv->prev && line->argv->next)
	{
		// printf("first node is redir and argv_head = second node\n");
		line->argv = line->argv->next;
		line->argv_head = line->argv;
		line->argv->prev = NULL;
		// free(line->argv->node);
		// free(line->argv);
	}
	else if (line->argv->prev && !line->argv->next)
	{
		// printf("last node is redir and last node becomes null\n");
		line->argv->prev->next = NULL;
		free(line->argv->node);
		// free(line->argv);
		line->argv = NULL;
		return (3);
	}
	else if (line->argv->prev && line->argv->next)
	{
		// printf("node is redir and argv = argv->next\n");
		line->argv->prev->next = line->argv->next;
		line->argv->next->prev = line->argv->prev;
		line->argv = line->argv->next;
		// free(line->argv->node);
		// free(line->argv);
	}
	return (1);
}

bool	process_redir(t_line *line, char redir_operator)
{
	short			offset;
	size_t			i;

	offset = redirection_offset(redir_operator);
	line->pipe->redir = malloc(sizeof(t_redir));
	if (!line->pipe->redir)
		return (false);
	while (is_white_space(line->argv->node[offset]))
		offset += 1;
	line->pipe->redir->type = redir_operator;
	line->pipe->redir->filename = malloc(sizeof(char) * \
		ft_strlen(line->argv->node) - offset + 1);
	if (!line->pipe->redir->filename)
		return (false);
	i = 0;
	while (line->argv->node[offset])
		line->pipe->redir->filename[i++] = line->argv->node[offset++];
	line->pipe->redir->filename[i] = '\0';
	if (!*line->pipe->redir->filename && !line->argv->next)
		return (printf("redir into newline\n"), false);
	printf("\tfilename: %s\n", line->pipe->redir->filename);
	return (true);
}

static char	tag_redirection(t_line *line)
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
	else if (!operator)
		return (2);
	else
		return (0);
	return (1);
}

static bool	tag_cmd_and_arg(t_line *line)
{
	size_t	node_count;

	node_count = count_argv_nodes(line);
	// if (!node_count)
	// 	return (true);
	line->pipe->arg = malloc(node_count + 1 * sizeof(char *));
	if (!line->pipe->arg)
		return (false);
	while (line->argv && line->pipe->arg)
	{
		*line->pipe->arg = ft_strdup(line->argv->node);
		if (!*line->pipe->arg)
			return (false);
		printf("\t     ARG: %s\n", *line->pipe->arg);
		*line->pipe->arg += 1;
		line->argv = line->argv->next;
	}
	return (true);
}

static bool	handle_redir(t_line *line)
{
	char	return_value;
	char	good_redir;

	while (line->argv && *line->argv->node != '|')
	{
		good_redir = tag_redirection(line);
		if (good_redir == 1)
		{
			return_value = extract_node(line);
			if (return_value == 3)
				break ;
			// else if (return_value == 2)
			// 	return (false);
			else if (return_value == 1)
				continue ;
			else if (!return_value)
				return (false);
		}
		else if (!good_redir)
			return (false);
		else
			line->argv = line->argv->next;
	}
	return (true);
}

bool	parse(t_line *line)
{
	line->argv = line->argv_head;
	if (!clean_surrounding_quotes(line))
		return (printf("clean_quotes_failed\n"), false);
	line->pipe = malloc(sizeof(t_pipe));
	if (!line->pipe)
		return (false);
	line->argv = line->argv_head;
	while (line->pipe)
	{
		if (!handle_redir(line))
			return (false);
		line->argv = line->argv_head;
		if (!tag_cmd_and_arg(line))
			return (false);
		line->argv = line->argv_head;
		while ()
	}
	// free_t_line_argv();
	return (true);
}

/*
INIT PIPE
FILL_PIPE()
	WHILE (LINE->PIPE)
		WHILE (LINE->ARGV)
			if *NODE == '|'
				pipe = pipe->next;
			else if *NODE == REDIR_OP
				node = tag_redir();
			else if *NODE == ARG
				node = tag_arg()
			else
				argv = argv->next;
*/