/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:49:30 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/04 20:53:50 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// 	subtoken = line->argv->node;
// 	while (*subtoken && is_env_var_name_format(*subtoken))
// 		subtoken += 1;
// 	token_one = ft_substr(line->argv->node, 0, subtoken - line->argv->node);
// 	if (!token_one || !*token_one)
// 		return ;
// 	while (*line->argv->node++)
// 		;
// 	token_two = ft_substr(subtoken, 0, line->argv->node - subtoken);
// 	if (!token_two || !*token_two)
// 		return ;
// }
//static void	true_expand(/*t_line *line*/)
//{
	// char	*var;
	// char	*cpy;

	// cpy = line->argv->node + 2;
	// while (is_env_var_name_format(cpy))
		// cpy++;
	// if (!cpy || !*cpy)	?
		// return (false); ?
	// var = get_var_from_envp();
	// if (!var)
	// 	return ((void)printf("env_var not found"));
	// ft_str_append(line->argv->node, var);
//}

static bool	handle_dollar_sign(t_line *line)
{
	// line->argv->node += 1;
	if ((*line->argv->node && !is_env_var_name_format(*(line->argv->node + 1)))
		|| !*line->argv->node)
		return (false);
	// line->argv->node += 1;
	// true_expand(line);
	return (false);
}
// ================================ EXPAND_UTILS ==============================

bool	expand(t_line *line)
{
	while (line->argv)
	{
		while (*line->argv->node++)
		{
			if (*line->argv->node == '$')
				if (!handle_dollar_sign(line))
					return (false);
		}
		line->argv->node += 1;
	}
	return (true);
}
