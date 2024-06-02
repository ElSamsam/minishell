/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:10:09 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/23 16:29:23 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quote(char c, char quote)
{
	if (c == quote)
		return (true);
	return (false);
}

const char	*skip_quote_content(const char *str, char quote)
{
	if (*str == '\'' || *str == '"')
		str += 1;
	while (*str && !is_quote(*str, quote))
		str++;
	if (*str == '\'' || *str == '"')
		return (str + 1);
	return (str);
}
