/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_big_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:22:22 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/02 01:17:51 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../I_header/minishell.h"

static void	print_lst(t_line *line)
{
	if (line && line->argv && line->pipe && line->pipe->cmd \
	&& line->pipe->cmd->arg && *line->pipe->cmd->arg \
	&& line->pipe->redir && line->pipe->redir->type \
	&& line->pipe->redir->filename \
	&& line->pipe->redir->type \
	&& line->pipe->redir->type)
	{
		line->argv = line->argv_head;
		while (line->argv)
		{
			printf("%s\n", line->argv->node);
		}
	}
}

// TODO turn all malloc into calloc
bool	big_parse(t_line *line, char **input)
{
	char	*str;
	if (!*input || !input)
		return (false);
	skip_white_spaces((const char **)input);
	if (!**input)
		return (false);
	str = *input;
	if (clean_input((const char **)&str))
		write(1, "CLEAN_INPUT\n\n", 13);
	else
		return (write(1, "BAD_INPUT\n\n", 11), false);
	if (lex((const char *)str, line))
		printf("GOOD_LEX\n\n");
	else
		return (printf("BAD_LEX\n\n"), false);
	if (parse(line))
		printf(/*print_lst(line), */"GOOD_PARSE\n\n");
	else
		return (printf("BAD_PARSE\n\n"), false);
	// else
		// return (printf("BAD_LEX\n"), false);
		// if (expand(line))
		// printf("CASH_MONEY\nargc = %i\n", line->argc);
	// else
	// 	return (printf("BROKE_ASS\n"), false);
		// check_path(intput);
	return (true);
}
