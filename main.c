/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 06:39:58 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/21 22:13:51 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./I_header/minishell.h"

int	main(void)
{
	char	*str;
	t_line	line;

	while (13)
	{
		str = readline(">> minishell ");
		if (str)
		{
			add_history(str);
			big_parse(&line, &str);
			if (*str)
				free(str);
		}
		else
			printf("%s: command not found\n", str);
	}
	rl_clear_history();
	return (0);
}
