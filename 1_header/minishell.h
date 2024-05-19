/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:33:51 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/19 01:46:43 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "../3_libft_improved/libft.h"

typedef struct s_redir
{
	int					type;
	char				*arg;
}	t_redir;

typedef struct s_cmd
{
	char			**arr;
	t_redir			*in_out;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_line
{
	t_cmd	*cmd;
	char	**env;
}	t_line;

// =================================== PARSING ================================

int		main(void);
void	big_parse(t_line *line, char *input);
bool	clean_input(char *input);
void	lex(char *input, t_line *line);

bool	is_white_space(char c);
void	skip_white_spaces(const char **input);

short	count_redirection_operators(const char *input);

// =================================== PARSING ================================

#endif