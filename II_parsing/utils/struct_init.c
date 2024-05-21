/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:30:37 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/22 01:24:15 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../I_header/minishell.h"

t_line	*make_t_line_argv_node(const char *input, size_t len, t_line *line)
{
	static char	i = 1;

	if (line->argc > 0)
		line->argv->prev = line->argv;
	line->argv = malloc(sizeof(t_argv));
	if (!line->argv)
		return (NULL);
	line->argv->node_index = i++;
	line->argc += 1;
	line->argv->av = ft_substr((const char *)input, 0, len);
	if (!line->argv->av)
		return (NULL);
	if (line->argc == 0)
		line->argv->prev = NULL;
	line->argv->next = NULL;
	return (line);
}
