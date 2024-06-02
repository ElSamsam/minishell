/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:10:46 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/01 23:32:17 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../I_header/minishell.h"

bool	clean_input(const char **str)
{
	skip_white_spaces((const char **)str);
	if (!*str)
		return (false);
	if (!quotes(*str))
		return (false);
	// if (!good_redirections(*str))
	// 	return (false);
	return (true);
}
