/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 00:21:21 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/30 04:27:59 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../I_header/minishell.h"

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
// 
// how again?
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
				return (++str);
		}
		if (!*str)
			return (NULL);
		str++;
	}
	return (str);
}

// TODO fix redir into newline condition line 119-120
bool	good_redirections(const char *str)
{
	const char	*return_value;

	return_value = bad_redirection(str);
	if (!return_value)
		return (false);
	if (is_redirection_operator(--return_value) == IN_REDIR)
		return (printf("syntax error near unexpected token `<'\n"), false);
	else if (is_redirection_operator(return_value) == OUT_REDIR)
		return (printf("syntax error near unexpected token `>'\n"), false);
	else if (is_redirection_operator(return_value) == APPEND)
		return (printf("syntax error near unexpected token `>>'\n"), false);
	else if (is_redirection_operator(return_value) == HEREDOC)
		return (printf("syntax error near unexpected token `<<'\n"), false);
	// else if (*str && !is_valid_fd_name(*(return_value - 1)))
	// 	return (printf("redir into %c\n", *(return_value - 1)), false);
	else if (is_valid_fd_name(*(return_value)))
		return (true);
	if (!*return_value)
		return (printf("syntax error near unexpected token `newline'\n") \
			, false);
	return (true);
}
