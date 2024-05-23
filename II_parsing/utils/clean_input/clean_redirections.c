/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 00:21:21 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/24 17:43:35 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../I_header/minishell.h"
#include <stdbool.h>
#include <stdio.h>

char	skip_redirection_operator(const char **str)
{
	if ((*str)[0] == '<' && (*str)[1] == '<')
		return (*(str) += 2, 4);
	else if ((*str)[0] == '>' && (*str)[1] == '>')
		return (*(str) += 2, 3);
	else if (**str == '<')
		return (*(str) += 1, 2);
	else if (**str == '>')
		return (*(str) += 1, 1);
	return (false);
}

char	is_redirection_operator(const char *str)
{
	if (str[0] == '<' && str[1] == '<')
		return (4);
	else if (str[0] == '>' && str[1] == '>')
		return (3);
	else if (*str == '>')
		return (2);
	else if (*str == '<')
		return (1);
	return (0);
}

bool	is_valid_fd_name(char c)
{
	if (ft_isalnum((int)c) || c == '_' || c == '.' || c == '-' || c == '/'
		|| c == '$' || c == '\'' || c == '"')
		return (true);
	return (false);
}

static const char	*whos_bad(const char *str)
{
	skip_white_spaces(&str);
	if (!*str || !str)
		return (NULL);
	if (is_redirection_operator(str))
		return (str);
	while (is_valid_fd_name(*str))
	{
		if (*str == '\'' || *str == '"')
		{
			str = skip_quote_content(str, '\'');
			str = skip_quote_content(str, '"');
			if (*str && is_redirection_operator(str))
				return (str);
		}
		else
			str += 1;
	}
	return (str);
}

// THIS IS GONNA HANDLE ACCESS() TO FD IN THE FUTURE
const char	*bad_redirection(const char *str)
{
	while (*str)
	{
		if (skip_redirection_operator(&str))
		{
			if (!*str)
				return (str);
			str = whos_bad(str);
			if (!str)
				return (NULL);
			if (!*str)
				return (str);
			if (is_redirection_operator(str))
				return (str);
		}
		if (!*str)
			return (NULL);
		str++;
	}
	return (str);
}

bool	good_redirections(const char *str)
{
	const char	*return_value;

	return_value = bad_redirection(str);
	if (!return_value)
		return (false);
	if (is_redirection_operator(--return_value) == 1)
		return (printf("syntax error near unexpected token `<'\n"), false);
	else if (is_redirection_operator(return_value) == 2)
		return (printf("syntax error near unexpected token `>'\n"), false);
	else if (is_redirection_operator(return_value) == 3)
		return (printf("syntax error near unexpected token `>'>\n"), false);
	else if (is_redirection_operator(return_value) == 4)
		return (printf("syntax error near unexpected token `<'<\n"), false);
	// else if (*str && !is_valid_fd_name(*(return_value - 1)))
	// 	return (printf("redir into %c\n", *(return_value - 1)), false);
	else if (is_valid_fd_name(*(return_value)))
		return (true);
	else if (!*return_value)
		return (printf("redir into newline\n"), false);
	return (true);
}
