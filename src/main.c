/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 06:39:58 by saperrie          #+#    #+#             */
/*   Updated: 2024/06/03 01:05:27 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// (argc + argv + 1 = envp);in memory, thanks geymat for the tip
// TODO get_env(user); >>>> readline(user);
int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	t_line	line;

	(void)argc;
	(void)argv;
	if (*envp)
		line.env = envp;
	while (13)
	{
		str = readline(">> minishell ");
		if (str)
		{
			add_history(str);
			big_parse(&line, &str);
			// if (*str && str)
			// 	free(str);
		}
		else
			printf("%s: command not found\n", str);
	}
	rl_clear_history();
	return (0);
}
