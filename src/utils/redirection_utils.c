/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:21:34 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/07 22:41:19 by saperrie         ###   ########.fr       */
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

char	skip_redirection_operator(char **str)
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

char	is_redirection_operator(char *str)
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

size_t	count_argv_nodes(t_line *line)
{
	size_t	node_count;

	node_count = 0;
	while (line->argv)
	{
		node_count += 1;
		line->argv = line->argv->next;
	}
	line->argv = line->argv_head;
	return (node_count);
}