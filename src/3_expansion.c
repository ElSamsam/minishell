/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:49:30 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/17 18:51:21 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static char	*handle_dollar(t_line *line, char *ptr)
{
	char	*s1;
	char	*tmp;
	char	*value;
	char	*rest;
	char	*new_node;
	size_t	i;
	size_t	name_len;

	name_len = 0;
	if (*ptr != *line->argv->node)
		s1 = ft_substr(line->argv->node, 0, ptr - line->argv->node);
	tmp = ptr + 1;
	while (is_valid_varname(*(tmp++)))
		name_len++;
	// FT_GET_VALUE();
	while (env[i] && !match_found)
		match_found = ft_strncmp(ptr, line->env[i++], name_len);
	if (match_found)
		value = ft_strdup(line->env[i - 1]);
	else
		value = ft_calloc(1, 1);
	// 
	rest = ft_strdup(&line->argv->node[ptr - line->argv->node] + name_len);
	if (!rest)
		return (0);
	new_node = ft_strjoin(value, rest);
	if (s1)
		new_node = ft_strjoin(s1, ft_strjoin(value, rest));
	if (!new_node)
		return (0);
	free(line->argv->node);
	line->argv->node = new_node;
	return (tmp);
}

bool	expand(t_line *line)
{
	char	*ptr;

	line->argv = line->argv_head;
	while (line->argv)
	{
		ptr = line->argv->node;
		while (*ptr)
		{
			if (*ptr == '$')
				ptr = handle_dollar(line, ptr);
			ptr += 1;
		}
		line->argv = line->argv->next;
	}
}

// bool	expand(t_line *line)
// {
// 	while (line->argv)
// 	{
// 		while (*line->argv->node++)
// 		{
// 			if (*line->argv->node == '$')
// 				if (!handle_dollar_sign(line))
// 					return (false);
// 			line->argv->node += 1;
// 		}
// 		line->argv = line->argv->next;
// 	}
// 	return (true);
// }
