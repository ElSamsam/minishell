/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:33:51 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/20 00:52:32 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "../III_libft_improved/src/libft.h"

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
void	big_parse(t_line *line, char **input);
bool	clean_input(char **input);
void	lex(char *input, t_line *line);

// W_SPACE
bool	is_white_space(char c);
void	skip_white_spaces(const char **input);
// W_SPACE

// QUOTES
bool	quotes(char *str);
char	*find_matching_quote(char *str, char quote);
bool	even_quotes(char *str);
// QUOTES

// REDIRECTIONS
bool	good_redirections(char *str);
char	bad_redirection(const char *str);
bool	is_valid_fd_name(char c);
char	is_redirection_operator(const char *str);
char	skip_redirection_operator(const char **str);
// REDIRECTIONS

// short	count_redirection_operators(const char *input);

// =================================== PARSING ================================

#endif