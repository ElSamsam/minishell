/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:55:40 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/31 17:06:25 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../I_header/minishell.h"

static bool	process_out(t_line *line, char redir_operator)
{
	size_t	i;

	i = 0;
	line->pipe->redir->out = malloc(sizeof(t_type));
	if (!line->pipe->redir->out)
		return (false);
	line->pipe->redir->out->redir_type = redir_operator;
	line->pipe->redir->out->file_name = malloc(ft_strlen(line->argv->av));
	while (line->argv->av[i])
	{
		line->pipe->redir->out->file_name[i] = line->argv->av[i];
		i += 1;
	}
	return (true);
}

// NEED TO SKIP REDIR OP AND WSPACES BUT DO NOT INCREMENT THE POINTER SO THAT I CAN FREE IT LATER
static bool	process_in(t_line *line, char redir_operator)
{
	size_t	i;

	i = 0;
	line->pipe->redir->in = malloc(sizeof(t_type));
	if (!line->pipe->redir->in)
		return (false);
	line->pipe->redir->in->redir_type = redir_operator;
	line->pipe->redir->in->file_name = malloc(ft_strlen(line->argv->av));
	while (line->argv->av[i])
	{
		line->pipe->redir->in->file_name[i] = line->argv->av[i];
		i += 1;
	}
	return (true);
}

static bool	process_redir(t_line *line, char redir_operator)
{
	line->pipe->redir = malloc(sizeof(t_redir));
	if (!line->pipe->redir)
		return (false);
	if (redir_operator == IN_REDIR || redir_operator == HEREDOC)
	{
		if (!process_in(line, redir_operator))
			return (false);
	}
	else if (redir_operator == OUT_REDIR || redir_operator == APPEND)
	{
		if (!process_out(line, redir_operator))
			return (false);
	}
	return (true);
}

static bool	tag_redirections(t_line *line)
{
	char	redir_type;

	redir_type = is_redirection_operator((line->argv->av));
	if (redir_type == IN_REDIR)
		process_redir(line, IN_REDIR);
	else if (redir_type == OUT_REDIR)
		process_redir(line, OUT_REDIR);
	else if (redir_type == APPEND)
		process_redir(line, APPEND);
	else if (redir_type == HEREDOC)
		process_redir(line, HEREDOC);
	else
		return (false);
	return (true);
}

//  TODO how the hell is this suppposed to be workin
static bool	extract_node(t_line *line)
{
	t_argv	*tmp;

	tmp = line->argv;
	if (!line->argv->prev && !line->argv->next)
	{
		// free(tmp->av);
		// free(tmp);
	}
	else if (!line->argv->prev && line->argv->next)
	{
		line->argv = line->argv->next;
		line->lst_head = line->argv;
		// free(tmp->av);
		// free(tmp);
	}
	else if (line->argv->prev && !line->argv->next)
	{
		// line->argv = line->argv->prev;
		line->argv->prev->next = NULL;
		// free(tmp->av);
		// free(tmp);
	}
	else if (line->argv->prev && line->argv->next)
	{
		line->argv->prev->next = line->argv->next;
		line->argv->next->prev = line->argv->prev;
		printf("redir_node %i : %s\n", line->argv->node_index, line->argv->av);
		line->argv = line->argv->next;
		// free(tmp->av);
		// free(tmp);
	}
	return (true);
}

static bool	tag_tokens(t_line *line)
{
	while (line->argv)
	{
		if (tag_redirections(line))
			extract_node(line);
		else if (line->argv)
			line->argv = line->argv->next; // FIX THIS SHIT LINE NEXT THINGY
	}
	// tag_cmd_and_arg();
	return (true);
}

// TODO need to factorise this function for singles and doubles
static bool	clean_surrounding_quotes(t_line *line)
{
	size_t	i;
	size_t	j;
	char	s_quote;
	char	d_quote;

	s_quote = 0;
	d_quote = 0;
	if (!line->argv)
		return (false);
	while (line->argv)
	{
		i = 0;
		j = 0;
		while (line->argv->av && line->argv->av[j]) // && line->argv->av[i])
		{
			if (line->argv->av[i] != '"')
				line->argv->av[j++] = line->argv->av[i++];
			else if (line->argv->av[i] == '"' && d_quote) // && line->argv->av[i])
			{
				d_quote = 0;
				i++;
			}
			else if (line->argv->av[i] == '"' && !d_quote)
			{
				d_quote = 1;
				i++;
			}
		}
		printf("\tclean%i: %s\n", line->argv->node_index, line->argv->av);
		line->argv = line->argv->next;
	}
	return (true);
}

bool	parse(t_line *line)
{
	line->argv = line->lst_head;
	if (!clean_surrounding_quotes(line))
		return (printf("clean_quotes_failed\n"), false);
	line->pipe = malloc(sizeof(t_pipe));
	if (!line->pipe)
		return (false);
	line->argv = line->lst_head;
	// tag_tokens(line);
	return (true);
}
