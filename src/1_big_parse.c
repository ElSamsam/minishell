/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_big_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:22:22 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/03 06:53:50 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if heredoc limiter contains quote : cat << "H"D
// 										<< $USER
// 										<< HD
// 				don't expand, result is : $USER 

static bool	clean_input(const char **str)
{
	skip_white_spaces((const char **)str);
	if (!*str)
		return (false);
	if (!quotes(*str))
		return (false);
	return (true);
}

// TODO turn all malloc into calloc
bool	big_parse(t_line *line, char **input)
{
	char	*str;
	if (!*input || !input)
		return (false);
	skip_white_spaces((const char **)input);
	if (!**input)
		return (false);
	str = *input;
	if (clean_input((const char **)&str))
		write(1, "CLEAN_INPUT\n", 12);
	else
		return (write(1, "BAD_INPUT\n", 10), false);
	if (lex((const char *)str, line))
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
