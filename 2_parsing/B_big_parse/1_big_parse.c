/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_big_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:22:22 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/19 00:17:56 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

static void	ft_echo(char *str)
{
	if (*str == 'e' && *str + 1 == 'c' && *str + 2 == 'h' && *str + 3 == 'o')
	{
		char *const *double_ptr = &str;
		execve("bin/echo", double_ptr, NULL);
	}
}

void	big_parse(t_line *line, char *input)
{
	// tokenise(line, input);
	// ft_echo(input);
	char	*str;

	str = input;
	if (!*input || clean_input(input))
		return ;
	// lex(str, line);
	// expand(input);
	// parse(input);
	// check_path(intput);
}