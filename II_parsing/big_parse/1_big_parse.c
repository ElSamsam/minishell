/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_big_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:22:22 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/21 16:51:27 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../I_header/minishell.h"
#include <unistd.h>

void	big_parse(t_line *line, char **input)
{
	char	*str;

	str = *input;
	line->argc = 0;
	if (clean_input(&str))
	{
		write(1, "CLEAN_INPUT\n", 13);
		lex(str, line);
	}
	// expand(input);
	// parse(input);
	// check_path(intput);
}
