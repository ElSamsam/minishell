/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:49:30 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/20 22:07:06 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_varname(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

// static char	*get_env_value(t_line *line, char *ptr, size_t name_len)
// {
// 	int		match_found;
// 	size_t	i;
// 	char	*value;

// 	match_found = 0;
// 	i = 0;
// 	while (line->env[i] && !match_found)
// 		match_found = ft_strncmp(ptr, line->env[i++], name_len);
// 	if (match_found)
// 		value = ft_strdup(line->env[i - 1]);
// 	else
// 		value = ft_calloc(1, 1);
// 	if (value)
// 		return (value);
// 	return (NULL);
// }

static char	*handle_dollar(t_line *line, char *ptr)
{
	char	*s1;
	char	*name;
	char	*tmp;
	char	*value;
	char	*rest;
	char	*new_node;
	size_t	name_len;

	name_len = 0;
	s1 = NULL;
	if (*ptr != *line->argv->node)
		s1 = ft_substr(line->argv->node, 0, ptr - line->argv->node);
	tmp = ptr + 1;
	while (is_valid_varname(*(tmp++)))
		name_len++;
	name = ft_substr(ptr, 1, name_len);
	printf("		NAME:%s\n", name);
	if (!name)
		return (NULL);
	value = getenv(name);
	printf("		VALUE:%s\n", value);
	if (!value)
		return (NULL);
	if (name)
		free(name);
	rest = ft_strdup(&line->argv->node[name_len + 2]);
	if (!rest)
		return (NULL);
	if (s1)
		new_node = ft_strjoin(s1, ft_strjoin(value, rest));
	else
		new_node = ft_strjoin(value, rest);
	if (!new_node)
		return (NULL);
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
			if (!ptr)
				return (false);
			ptr += 1;
		}
		line->argv = line->argv->next;
	}
	return (true);
}

