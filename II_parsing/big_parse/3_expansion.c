/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:49:30 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/23 22:04:02 by saperrie         ###   ########.fr       */
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


// IN PROGRESS
// static void	split_tokens(t_line *line)
// {
// 	char	*subtoken;
// 	char	*token_one;
// 	char	*token_two;

// 	subtoken = line->argv->av;
// 	while (*subtoken && is_env_var_name_format(*subtoken))
// 		subtoken += 1;
// 	token_one = ft_substr(line->argv->av, 0, subtoken - line->argv->av);
// 	if (!token_one || !*token_one)
// 		return ;
// 	while (*line->argv->av++)
// 		;
// 	token_two = ft_substr(subtoken, 0, line->argv->av - subtoken);
// 	if (!token_two || !*token_two)
// 		return ;
// }

static void	true_expand(t_line *line)
{
	// char	*var;
	// char	*cpy;

	// cpy = line->argv->av + 2;
	// while (is_env_var_name_format(cpy))
		// cpy++;
	// if (!cpy || !*cpy)	?
		// return (false); ?
	// var = get_var_from_envp();
	// if (!var)
	// 	return ((void)printf("env_var not found"));
	// ft_str_append(line->argv->av, var);
}

static bool	handle_dollar_sign(t_line *line)
{
	// line->argv->av += 1;
	if ((*line->argv->av && !is_env_var_name_format(*(line->argv->av + 1)))
		|| !*line->argv->av)
		return (false);
	// line->argv->av += 1;
	// true_expand(line);
	return (false);
}
// ================================ EXPAND_UTILS ==============================

bool	expand(t_line *line)
{
	while (line->argv++)
	{
		while (*line->argv->av++)
		{
			if (*line->argv->av == '$')
				if (!handle_dollar_sign(line))
					return (false);
		}
		line->argv->av += 1;
	}
	return (true);
}
