/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 00:07:21 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/01 23:51:07 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../I_header/minishell.h"

// TODO need to factorise this function for singles and doubles
// FIXME substr the clean node in line->argv->node because i, j, and node point to three different addresses
bool	clean_surrounding_quotes(t_line *line)
{
	size_t	i;
	size_t	j;
	char	s_quote;
	char	d_quote;

	s_quote = 0;
	d_quote = 0;
	if (!line->argv)
		return (false);
	j = 0;
	while (line->argv)
	{
		i = 0;
		while (line->argv->node[j]) // && line->argv->node[i])
		{
			if (line->argv->node[i] != '"') // HERE
				line->argv->node[j++] = line->argv->node[i++];
			else if (line->argv->node[i] == '"' && d_quote) // && line->argv->node[i])
			{
				d_quote = 0;
				i++;
			}
			else if (line->argv->node[i] == '"' && !d_quote)
			{
				d_quote = 1;
				i++;
			}
		}
		printf("\tclean%i: %s\n", line->argv->node_index, line->argv->node);
		line->argv = line->argv->next;
	}
	return (true);
}

const char	*find_matching_quote(const char *str, char quote)
{
	while (*str)
	{
		if (*str == quote)
			return (str);
		str++;
	}
	return (NULL);
}

bool	even_quotes(const char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			str = find_matching_quote(++str, '\'');
			if (!str)
				return (false);
		}
		else if (*str == '"')
		{
			str = find_matching_quote(++str, '"');
			if (!str)
				return (false);
		}
		str++;
	}
	return (true);
}

bool	quotes(const char *str)
{
	if (!even_quotes(str))
		return (printf("minishell: parsing error: missing quote\n"), (false));
	// if (terrible_input(str))
	// 	return (printf("nice try :)"), (false));
	return (true);
}
