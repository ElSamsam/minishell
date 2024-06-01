/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:55:40 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/01 03:03:08 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../I_header/minishell.h"
#include <stdbool.h>

//  FIXME this suppposed to be workin and 5 functions
static char	extract_node(t_line *line)
{
	t_argv	*tmp;

	tmp = line->argv;
	if (!line->argv->prev && !line->argv->next)
	{
		printf("\nonly node in lst->argv is a redir\n");
		free(tmp->node);
		free(tmp);
		if (line->argc == 1)
			return (0);
	}
	else if (!line->argv->prev && line->argv->next)
	{
		line->argv = line->argv->next;
		line->argv_head = line->argv;
		line->argv->prev = NULL;
		printf("\nfirst node is redir and argv_head = second node\n");
		free(tmp->node);
		free(tmp);
	}
	else if (line->argv->prev && !line->argv->next)
	{
		// line->argv = line->argv->prev;
		printf("\nlast node is redir and last node becomes null\n");
		line->argv->prev->next = NULL;
		free(tmp->node);
		free(tmp);
		return (2);
	}
	else if (line->argv->prev && line->argv->next)
	{
		printf("\nnode is redir and argv_head = node->next\n");
		line->argv->prev->next = line->argv->next;
		line->argv->next->prev = line->argv->prev;
		printf("redir_node %i : %s\n", line->argv->node_index, line->argv->node);
		line->argv = line->argv->next;
		free(tmp->node);
		free(tmp);
	}
	return (1);
}

static bool	tag_redirections(t_line *line)
{
	char	operator;

	if (!line->argv->node || !line->argv || !line->argv)
		return (false);
	operator = is_redirection_operator((line->argv->node));
	if (operator == IN_REDIR && process_redir(line, IN_REDIR))
		;
	else if (operator == OUT_REDIR && process_redir(line, OUT_REDIR))
		;
	else if (operator == APPEND && process_redir(line, APPEND))
		;
	else if (operator == HEREDOC && process_redir(line, HEREDOC))
		;
	else
		return (false);
	return (true);
}

static bool	tag_tokens(t_line *line)
{
	char	return_value;

	while (line->argv)
	{
		if (tag_redirections(line))
		{
			return_value = extract_node(line);
			if (return_value == 2)
				return (true);
			else if (return_value == 1)
				continue ;
			else if (!return_value)
				return (false);
		}
		else
			line->argv = line->argv->next; // FIX THIS LINE->NEXT THINGY
	}
	// tag_cmd_and_arg();
	// free_t_line_argv();
	return (true);
}

//  FIXME fix clean_surrounding_quotes()
bool	parse(t_line *line)
{
	// line->argv = line->argv_head;
	// if (!clean_surrounding_quotes(line))
	// 	return (printf("clean_quotes_failed\n"), false);
	line->pipe = malloc(sizeof(t_pipe));
	if (!line->pipe)
		return (false);
	line->argv = line->argv_head;
	if (!tag_tokens(line))
		return (false);
	return (true);
}
