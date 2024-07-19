/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 01:03:09 by saperrie          #+#    #+#             */
/*   Updated: 2024/07/19 01:51:53 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	rearrange_prev_next_in_argv_nodes(t_line *line, char **strs)
{
	t_line	*new_line;

	new_line = ft_calloc(1, sizeof(t_line));
	if (!new_line)
		return (false);
	new_line->argc = 0;
	while (*strs)
		make_argv_node(*strs++, ft_strlen(*strs), new_line);
}

static bool	insert_new_nodes(t_line *line, char **new_nodes, int node_index)
{
	bool	rearranged;

	rearranged = false;
	while (node_index != line->argv->node_index)
		line->argv = line->argv->next;
	free(line->argv->node);
	line->argv->node = *new_nodes;
	rearranged = rearrange_prev_next_in_argv_nodes(line, new_nodes);
	if (!rearranged)
		return (true);
	return (false);
}

static bool	wspace_within_quotes(t_line *line)
{
	char	*str;
	bool	inside_quote;

	inside_quote = -1;
	str = line->argv->node;
	while (str)
	{
		if (*str == '"')
			inside_quote *= -1;
		if (inside_quote == 1 && (*str == ' ' || *str == '\t'))
			return (true);
		str += 1;
	}
	return (false);
}

bool	str_contains_wspace(char *str)
{
	while (*str)
	{
		if (*str == ' ')
			return (true);
	}
	return (false);
}

bool	potential_split_after_expand(t_line *line)
{
	char	**new_nodes;

	while (line->argv)
	{
		if (!str_contains_wspace(line->argv->node))
		{
			line->argv = line->argv->next;
			if (!line->argv)
				return (true);
			continue ;
		}
		if (wspace_within_quotes(line))
		{
			new_nodes = ft_split(line->argv->node, ' '); // TODO ADD CHARSET FOR WSPACES
			if (!new_nodes)
				return (false);
			insert_new_nodes(line, new_nodes, line->argv->node_index);
		}
		line->argv = line->argv->next;
	}
	return (true);
}
