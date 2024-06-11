/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_big_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:22:22 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/11 17:08:51 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

// if heredoc limiter contains quote : cat << "H"D
// 										<< $USER
// 										<< HD
// 				don't expand, result is : $USER 

static	bool	dirty_redir(char *str)
{
	while (*str)
	{
		if (skip_redirection_operator(&str))
		{
			skip_white_spaces(&str);
			if (*str == '|')
				return (ft_putstr_fd \
			("syntax error near unexpected token `newline'\n", 2), false);
		}
		str += 1;
	}
	return (true);
}

static bool	clean_input(char **str)
{
	skip_white_spaces((char **)str);
	if (!*str)
		return (false);
	if (**str == '|')
		return (ft_putstr_fd \
	("minishell: syntax error near unexpected token `|'\n", 2), \
			false);
	if (!even_quotes(*str))
		return (ft_putstr_fd("minishell: parsing error: missing quote\n", 2) \
	, false);
	if (!dirty_redir(*str))
		return (false);
	return (true);
}

bool	big_parse(t_line *line, char **input)
{
	char	*str;

	if (!*input || !input)
		return (false);
	skip_white_spaces((char **)input);
	if (!**input)
		return (false);
	str = *input;
	if (clean_input((char **)&str))
		write(1, "CLEAN_INPUT\n", 12);
	else
		return (write(1, "BAD_INPUT\n", 10), false);
	if (lex((char *)str, line))
		printf("GOOD_LEX\n");
	else
		return (printf("BAD_LEX\n"), false);
	if (parse(line))
		printf("GOOD_PARSE\n");
	else
		return (printf("BAD_PARSE\n"), false);
	// if (expand(line))
	// 	printf("CHA CHING\nargc = %i\n", line->argc);
	// else
	// 	return (printf(">:(\n"), false);
	// check_path(intput);
	return (true);
}
