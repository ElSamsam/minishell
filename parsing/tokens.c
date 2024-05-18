/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 03:27:40 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/13 04:24:25 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenise(t_line *line, char *input)
{
	int	word_count;
	int	word_size;

	word_count = count_words(input);
	line->cmd->arr = malloc(sizeof(char *) * (word_count + 1));
	if (!line->cmd->arr)
		return (NULL);
	// LOOPY LOOP
	skip_whitespace(input);
	if (!malloc_until_whitespace(line, input))
		return (NULL);
	else
		fill_line_cmd_array();
	// THAT'S A LOOP

//	while (*input < 9 && *input > 13 && *input != ' ' && *input)
}