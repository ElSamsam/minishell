/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:21:34 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/01 02:33:17 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../I_header/minishell.h"
#include <readline/chardefs.h>

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

static	char	redirection_offset(char redir_operator)
{
	if (redir_operator == HEREDOC || redir_operator == APPEND)
		return (2);
	else if (redir_operator == IN_REDIR || redir_operator == OUT_REDIR)
		return (1);
	return (0);
}

bool	process_redir(t_line *line, char redir_operator)
{
	char	offset;
	size_t	i;

	offset = redirection_offset(redir_operator);
	if (!offset)
		return (printf("redir does not start with redir op\n"), false);
	line->pipe->redir = malloc(sizeof(t_redir));
	if (!line->pipe->redir)
		return (false);
	while (is_white_space(line->argv->node[offset]))
		offset += 1;
	line->pipe->redir->type = redir_operator;
	line->pipe->redir->filename = malloc(ft_strlen(line->argv->node) \
		- offset);
	if (!line->pipe->redir->filename)
		return (false);
	i = 0;
	while (line->argv->node[offset])
	{
		line->pipe->redir->filename[i] = line->argv->node[offset];
		printf("filename %c\n", line->pipe->redir->filename[i]);
		offset += 1;
		i += 1;
	}
	// line->pipe->redir->filename[offset] = '\0';
	return (true);
}
