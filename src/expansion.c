/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:49:30 by saperrie          #+#    #+#             */
/*   Updated: 2024/07/18 01:08:49 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*get_new_node(char *s1, char *value, char *rest)
{
	if (s1)
		return (ft_strjoin(s1, ft_strjoin(value, rest)));
	return (ft_strjoin(value, rest));
}

static char	*get_env_value(t_line *line, char *name)
{
	char	**env;
	char	*value;
	int		name_len;

	env = line->env;
	name_len = ft_strlen(name);
	while (*env)
	{
		if (!ft_strncmp(name, *env, name_len) && *(*env + name_len) == '=')
		{
			value = ft_strdup(*env + name_len + 1);
			if (!value)
				return (NULL);
			return (value);
		}
		env++;
	}
	return (ft_calloc(1, 1));
}

static char	*get_s1_for_strjoin(t_line *line, char *ptr)
{
	char	*s1;

	s1 = NULL;
	if (*ptr != *line->argv->node)
		s1 = ft_substr(line->argv->node, 0, ptr - line->argv->node);
	return (s1);
}

static char	*handle_dollar(t_line *line, char *ptr, char *tmp, char *new_node)
{
	char	*s1;
	char	*name;
	char	*value;
	char	*rest;
	size_t	name_len;

	name_len = 0;
	s1 = get_s1_for_strjoin(line, ptr);
	tmp = ptr;
	while (is_valid_varname(*(++tmp)))
		name_len += 1;
	// name_len = get_name_length(tmp);
	name = ft_substr(ptr, 1, name_len);
	// printf("		NAME: %s\n", name);
	if (!name)
		return (NULL);
	value = get_env_value(line, name);
	// printf("		VALUE: %s\n", value);
	if (!value)
		return (NULL);
	if (name)
		free(name);
	rest = ft_strdup(&line->argv->node[name_len + _strlen(s1) + 1]);
	if (!rest)
		return (NULL);
	// printf("		REST: %s\n", rest);
	new_node = get_new_node(s1, value, rest);
	if (!new_node)
		return (NULL);
	// printf("		NEW_NODE: %s\n", new_node);
	free(line->argv->node);
	line->argv->node = new_node;
	return (new_node - 1);
}

bool	expand(t_line *line)
{
	char	*ptr;
	char	*tmp;
	char	*new_node;

	tmp = NULL;
	new_node = NULL;
	line->argv = line->argv_head;
	while (line->argv)
	{
		ptr = line->argv->node;
		// tmp = ptr;
		while (*ptr)
		{
			if (*ptr == '$' && (ptr[1] != '+' || ptr[1] != '=')) /* + = / . , : ~ ` ! # $ % ^ ( ) { } [ ] \ PRINT DOLLAR*/ // FOR OTHERS SPECIAL CHARACTERS DON'T (AND )
				ptr = handle_dollar(line, ptr, tmp, new_node);
			if (!ptr)
				return (false);
			ptr += 1;
		}
		line->argv = line->argv->next;
	}
	line->argv = line->argv_head;
	// if (!potential_split_after_expand(line))
	// 	return (false);
	return (true);
}
