/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:55:40 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/29 18:59:18 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../I_header/minishell.h"

// TODO NEED TO FACTORISE THIS FUNCTION FOR SINGLES AND DOUBLES
static bool	clean_surrounding_quotes(t_line *line)
{
	size_t	i;
	size_t	j;
	char	s_quote;
	char	d_quote;

	s_quote = 0;
	d_quote = 0;
	if (!line->argv)
		return (false);
	line->argv = line->lst_head;
	while (line->argv)
	{
		i = 0;
		j = 0;
		while (line->argv->av && line->argv->av[j]) // && line->argv->av[i] ??
		{
			if (line->argv->av[i] != '"')
				line->argv->av[j++] = line->argv->av[i++];
			else if (line->argv->av[i] == '"' && d_quote) // && line->argv->av[i] ??
			{
				d_quote = 0;
				i++;
			}
			else if (line->argv->av[i] == '"' && !d_quote)
			{
				d_quote = 1;
				i++;
			}
		}
		printf("CLEAN_NODE No%i\t%s\n", line->argv->node_index, line->argv->av);
		line->argv = line->argv->next;
	}
	return (true);
}

bool	parse(t_line *line)
{
	if (!clean_surrounding_quotes(line))
		return (printf("clean_quotes_failed\n"), false);
	// tag_slots(line);
	return (true);
}
