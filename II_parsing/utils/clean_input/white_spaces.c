/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   white_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:15:23 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/23 03:27:11 by saperrie         ###   ########.fr       */
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

void	skip_white_spaces(const char **input)
{
	if (!*input || !**input || !input)
		return ;
	while (is_white_space(**input))
		(*input)++;
}
