/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:49:30 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/23 02:47:07 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../I_header/minishell.h"

// ================================ EXPAND_UTILS ==============================
// handle_quote_dollar_sign(line);


										/*|| == '`' || == '-'*/
static bool	is_env_var_name_format(char c)
{
	if (c == '_' || ft_isalnum((int)c))
		return (true);
	return (false);
}

static void	split_tokens(t_line *line)
{
	char	*subtoken;
	char	*token_one;
	char	*token_two;
	size_t	env_var_len;

	subtoken = line->argv->av;
	while (*subtoken && is_env_var_name_format(*subtoken))
		subtoken += 1;
	env_var_len = subtoken - line->argv->av;
	token_one = ft_substr(line->argv->av, 0, env_var_len);
	if (!token_one || !*token_one)
		return ;
	while (*line->argv->av++)
		;
	token_two = ft_substr(subtoken, 0, line->argv->av - subtoken);
	if (!token_two || !*token_two)
		return ;
}

static bool	handle_dollar_sign(t_line *line)
{
	line->argv->av += 1;
	if ((*line->argv->av && (!is_env_var_name_format(*line->argv->av))
			|| !*line->argv->av))
		return (false);
	line->argv->av += 1;
	split_tokens(line);
	// true_expand(line);
	return (false);
}
// ================================ EXPAND_UTILS ==============================

bool	expand(t_line *line)
{
	size_t	i;
	char	quote_mode;

	quote_mode = -1;
	while (line->argv)
	{
		i = 0;
		while (line->argv->av[i])
		{
			if (line->argv->av[i] == '"')
				quote_mode *= -1;
			if (line->argv->av[i] == '$' && quote_mode == -1)
				handle_dollar_sign(line);
			// if (line->argv->av[i] == '$' && quote_mode == -1)
			// 	handle_quote_dollar_sign(line);
			else
				i += 1;
		}
		line->argv->av += 1;
	}
	return (true);
}
