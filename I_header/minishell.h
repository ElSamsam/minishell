/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:33:51 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/23 03:59:39 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../III_libft_improved/src/libft.h"

enum e_TOKENS
{
	CMD,
	ARG,
	REDIR_OP,
	PIPE,
};

enum e_REDIR_OPERATOR
{
	IN_OPERATOR,
	OUT_OPERATOR,
	APPEND_OPERATOR,
	HEREDOC_OPERATOR,
};

typedef struct s_redir
{
	int					type;
	char				*arg;
}	t_redir;

typedef struct s_cmd
{
	char			**arg;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_argv
{
	int				node_index;
	char			*av;
	struct s_argv	*next;
	struct s_argv	*prev;
}	t_argv;

typedef struct s_line
{
	t_argv	*argv;
	int		argc;
	char	token_index;
	t_cmd	*cmd;
	char	**env;
	t_redir	*in_out;
}	t_line;

// =================================== PARSING ================================

int			main(int argc, char *argv[], char *exp[]);
bool		big_parse(t_line *line, char **input);
bool		clean_input(const char **input);
bool		lex(const char *input, t_line *line);

// W_SPACE
bool		is_white_space(char c);
void		skip_white_spaces(const char **input);
// W_SPACE

// QUOTES
bool		quotes(const char *str);
const char		*find_matching_quote(const char *str, char quote);
bool		even_quotes(const char *str);
// QUOTES

// TOKENS_UTILS
bool		is_quote(char c, char quote);
bool		is_arg_format(char c);
char		*quote_mode(char *str, char quote, size_t *length);
const char	*skip_quote_content(const char *str, char quote);
// TOKENS_UTILS

// EXPANSION
bool		expand(t_line *line);
// EXPANSION

// STRUCT
t_line		*make_t_line_argv_node(const char *input, size_t len, t_line *line);
// STRUCT

// REDIRECTIONS
bool		good_redirections(const char *str);
char		bad_redirection(const char *str);
bool		is_valid_fd_name(char c);
char		is_redirection_operator(const char *str);
char		skip_redirection_operator(const char **str);
// REDIRECTIONS

// =================================== PARSING ================================

#endif