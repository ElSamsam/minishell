/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:49:30 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/25 16:33:25 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	_strlen(char const *str)
{
	size_t	string_length;

	string_length = 0;
	if (!str)
		return (0);
	while (str[string_length])
		string_length++;
	return (string_length);
}

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

static	char	*get_new_node(char *s1, char *value, char *rest)
{
	if (s1)
		return (ft_strjoin(s1, ft_strjoin(value, rest)));
	return (ft_strjoin(value, rest));
}

// static	size_t	get_name_length(char *tmp)
// {
// 	size_t	length;

// 	length = 0;
// 	while (is_valid_varname(*++tmp))
// 	{
// 		length += 1;
// 		// tmp += 1;
// 	}
// 	return (length);
// }

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
	value = getenv(name);
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
			if (*ptr == '$')
				ptr = handle_dollar(line, ptr, tmp, new_node);
			if (!ptr)
				return (false);
			ptr += 1;
		}
		line->argv = line->argv->next;
	}
	line->argv = line->argv_head;
	return (true);
}

// static	char	which_expand_case(t_line *line)
// {
// 	char	*str;

// 	str = line->argv->node;
// 	if (str[0] == '$' && str[1] == '\0')
// 		return (1);
// 	else if (*str == ' ')
// 	;
// 	return (*str);
// }

// bool	expand(t_line *line)
// {
// 	char	exp_case;

// 	line->argv = line->argv_head;
// 	exp_case = which_expand_case(line);
// 	return (true);
// }