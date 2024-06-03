/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:21:34 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/03 06:36:39 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	redirection_offset(char redir_operator)
{
	if (redir_operator == HEREDOC || redir_operator == APPEND)
		return (2);
	else if (redir_operator == IN_REDIR || redir_operator == OUT_REDIR)
		return (1);
	return (0);
}

char	skip_redirection_operator(const char **str)
{
	if ((*str)[0] == '<' && (*str)[1] == '<')
		return (*(str) += 2, HEREDOC);
	else if ((*str)[0] == '>' && (*str)[1] == '>')
		return (*(str) += 2, APPEND);
	else if (**str == '>')
		return (*(str) += 1, OUT_REDIR);
	else if (**str == '<')
		return (*(str) += 1, IN_REDIR);
	return (false);
}

char	is_redirection_operator(const char *str)
{
	if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	else if (str[0] == '>' && str[1] == '>')
		return (APPEND);
	else if (*str == '>')
		return (OUT_REDIR);
	else if (*str == '<')
		return (IN_REDIR);
	return (0);
}

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
