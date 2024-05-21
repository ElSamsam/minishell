/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_big_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:22:22 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/22 01:22:02 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../I_header/minishell.h"
#include <unistd.h>

bool	big_parse(t_line *line, char **input)
{
	char	*str;

	str = *input;
	line->argc = 0;
	if (clean_input(&str))
		write(1, "CLEAN_INPUT\n", 13);
	else
		return (write(1, "BAD_INPUT\n", 11), false);
	if (lex(str, line))
		printf("GOOD_LEX\nargc = %i\n", line->argc);
	else
		return (write(1, "BAD_LEX\n", 9), false);
		// expand(input);
		// parse(input);
		// check_path(intput);
	return (true);
}
