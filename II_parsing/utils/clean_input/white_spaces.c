/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   white_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:15:23 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/01 22:58:41 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../I_header/minishell.h"

bool	is_white_space(char c)
{
	// if (c == '\0')
	// 	return (false);
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

size_t	skip_white_spaces(const char **input)
{
	size_t	wspace_len;

	wspace_len = 0;
	if (!*input || !**input || !input)
		return (0);
	while (is_white_space(**input))
	{
		wspace_len += 1;
		(*input)++;
	}
	return (wspace_len);
}
