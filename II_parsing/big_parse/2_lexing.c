/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_lexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:08:18 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/20 23:47:22 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../I_header/minishell.h"
#include <stdbool.h>

void	lex(char *input, t_line *line)
{
	if (!make_tokens(input, line))
		printf("BAD_TOKEN\n");/*, free_all_this_bs(line)*/;
	// mark_dollar_for_interp(input);
	// split_bis();
}
