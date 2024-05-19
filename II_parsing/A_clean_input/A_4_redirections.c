/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_redirections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 00:21:21 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/19 18:25:17 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../I_header/minishell.h"

// =================================== REDIR ==================================
bool	skip_redirection_operator(const char **str)
{
	if (**str == '<' && **str + 1 == '<')
		return (*str += 2, true);
	else if (**str == '>' && **str + 1 == '>')
		return (*str += 2, true);
	else if (**str == '<')
		return (*str += 1, true);
	else if (**str == '>')
		return (*str += 1, true);
	return (false);
}

short	is_redirection_operator(const char *str)
{
	if (*str == '<' && *str + 1 == '<')
		return (4);
	else if (*str == '>' && *str + 1 == '>')
		return (3);
	else if (*str == '>')
		return (2);
	else if (*str == '<')
		return (1);
	return (0);
}

bool	redir_into_redir(const char *str)
{
	while (*str)
	{
		if (skip_redirection_operator(&str))
		{
			skip_white_spaces(&str);
			if (!*str)
				return (printf("minishell: "),
					printf("syntax error near unexpected token `newline'\n")
					, false);
		}
		else
			str++;
		if (is_redirection_operator(str))
			return (true);
	}
	if (!*str || !str)
		return (false);
	return (false);
}

// short	count_redirection_operators(const char *str)
// {
// 	short	redir_count;

// 	redir_count = 0;
// 	while (*str)
// 	{
// 		if (skip_redirection_operator(&str))
// 			redir_count++;
// 		else
// 			str++;
// 	}
// 	return (redir_count);
// }
// =================================== REDIR ==================================