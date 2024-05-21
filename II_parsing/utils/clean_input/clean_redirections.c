/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 00:21:21 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/21 22:11:05 by saperrie         ###   ########.fr       */
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
	if (ft_isalnum((int)c) || c == '_' || c == '.' || c == '-' || c == '/')
		return (true);
	return (false);
}

char	bad_redirection(const char *str)
{
	while (*str)
	{
		if (skip_redirection_operator(&str))
		{
			if (*str)
				skip_white_spaces(&str);
			if (!*str)
				return (5);
			if (is_redirection_operator(str))
			{
				return (is_redirection_operator(str));
			}
			else if (!is_valid_fd_name(*str))
				return (*str);
			while (is_valid_fd_name(*str))
				str++;
		}
		else if (*str == ' ' || *str == '\t')
			skip_white_spaces(&str);
		else
			str++;
	}
	return (99);
}

bool	good_redirections(char *str)
{
	char	return_value;

	return_value = bad_redirection(str);
	if (return_value == 1)
		return (printf("redir into <\n"), false);
	else if (return_value == 2)
		return (printf("redir into >\n"), false);
	else if (return_value == 3)
		return (printf("redir into >>\n"), false);
	else if (return_value == 4)
		return (printf("redir into <<\n"), false);
	else if (return_value == 5)
		return (printf("redir into null\n"), false);
	else if (!is_valid_fd_name(return_value))
		return (printf("redir into %c\n", return_value), false);
	return (true);
}
