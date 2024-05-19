/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_white_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:15:23 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/19 18:24:45 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../I_header/minishell.h"


// =================================== W_SPACE ================================
bool	is_white_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	else
		return (false);
}

void	skip_white_spaces(const char **input)
{
	if (!*input || !**input)
		return ;
	while (is_white_space(**input))
		(*input)++;
}

// static size_t	len_to_next_white_space(char *input)
// {
// 	size_t	len;

// 	len = 0;
// 	while (*input && !is_white_space(*input))
// 	{
// 		input++;
// 		len++;
// 	}
// 	return (len);
// }
// =================================== W_SPACE ================================