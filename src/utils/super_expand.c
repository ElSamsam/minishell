/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 01:03:09 by saperrie          #+#    #+#             */
/*   Updated: 2024/07/19 23:20:05 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	link_new_line_argv_to_line(t_line *new_line, t_line *line, int node_index)
{
	t_argv	*tmp_next;

	new_line->argv = new_line->argv_head;
	while (node_index != line->argv->node_index)
		line->argv = line->argv->next;
	line->argv->node = old_node;
	line->argv->node = new_line->argv->node;
	free(old_node);
	line->argv->next = tmp_next;
	line->argv->next = new_line->argv;
	while (new_line->argv->next)
		new_line->argv = new_line->argv->next;
	new_line->argv->next = tmp_next;
}

bool	make_new_nodes(char **strs)
{
	new_line->argc = 0;
	while (*strs)
	{
		new_line = make_argv_node(*strs, ft_strlen(*strs), new_line);
		if (!new_line)
			return (NULL);
		*strs += 1;
	}
	return (new_line);
}

static bool	insert_new_nodes(t_line *line, char **new_nodes, int node_index)
{
	t_line	*new_line;

	new_line = ft_calloc(1, sizeof(t_line));
	if (!new_line)
		return (NULL);
	new_line = make_new_nodes(new_nodes);
	if (!new_line)
		return (true);
	line = link_new_line_argv_to_line(new_line, line, node_index);
	if (!line)
		return (false);
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
