/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:45:06 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/17 16:06:56 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_tablen(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
		i += 1;
	return (i);
}

// TODO ADD redir->prev and redir->next
bool	process_redir(t_line *line, char redir_operator)
{
	short			offset;
	size_t			i;

	offset = redirection_offset(redir_operator);
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
		line->pipe->redir->filename[i++] = line->argv->node[offset++];
	line->pipe->redir->filename[i] = '\0';
	if (!*line->pipe->redir->filename && !line->argv->next)
		return (printf("redir into newline\n"), false);
	printf("\tfilename: %s\n", line->pipe->redir->filename);
	return (true);
}
