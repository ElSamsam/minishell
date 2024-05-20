/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_big_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:22:22 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/20 23:45:47 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../I_header/minishell.h"

void	big_parse(t_line *line, char **input)
{
	char	*str;

	str = *input;
	clean_input(&str);
	lex(str, line);
	// expand(input);
	// parse(input);
	// check_path(intput);
}
