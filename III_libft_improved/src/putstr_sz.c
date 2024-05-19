/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_sz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:34:39 by saperrie          #+#    #+#             */
/*   Updated: 2024/01/20 04:05:00 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	putstr_sz(char *s)
{
	size_t	length;

	length = 0;
	while (s[length])
		length++;
	return (write(1, s, length));
}
