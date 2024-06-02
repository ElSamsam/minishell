/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:21:34 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/02 04:49:25 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../I_header/minishell.h"

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
	line->pipe->redir->filename = malloc(sizeof(char) * \
		ft_strlen(line->argv->node) - offset + 1);
	if (!line->pipe->redir->filename)
		return (false);
	i = 0;
	while (line->argv->node[offset])
	{
		line->pipe->redir->filename[i] = line->argv->node[offset];
		offset += 1;
		i += 1;
	}
	line->pipe->redir->filename[i] = '\0';
	printf("\tfilename: %s\n", line->pipe->redir->filename);
	// printf("\t   type%i\n\v", line->pipe->redir->type);
	return (true);
}
