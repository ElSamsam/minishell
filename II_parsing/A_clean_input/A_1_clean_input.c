/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   I_clean_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:19:28 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/19 01:50:35 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../I_header/minishell.h"

bool	clean_input(char **str)
{
	skip_white_spaces((const char **)&str);
	if (!*str)
		return (false);
	// printf("EARFQUAKE\n");
	if (!quotes(*str))
		return (false);
	if (redir_into_redir(*str))
		return (printf("zanzibar\n"), false);
	return (true);
}