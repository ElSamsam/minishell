/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_lexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:08:18 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/20 01:56:34 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../I_header/minishell.h"

// static short	make_tokens(char *input, t_line *line, int i)
// {
// 	size_t	len;

// 	skip_white_spaces(&input);
// 	while (*input && !is_white_space(*input))
// 	{
// 		len = len_to_next_white_space(input);
// 		line->cmd->arr[i++] = ft_substr(input, 0, len);
// 	}
// }

void	lex(char *input, t_line *line)
{
	// make_tokens(input, line, 0);
	// clean_parasite_quotes(input);
	// mark_dollar_for_interp(input);
	// split_bis();
}
