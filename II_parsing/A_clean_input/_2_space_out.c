/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_space_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 00:21:17 by saperrie          #+#    #+#             */
/*   Updated: 2024/05/19 17:44:02 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// =================================== SPACE_OUT ==============================

static char	*ft_strncpy(char *dest, char *src, size_t length)
{
	size_t	i;

	i = 0;
	while (src[i] && i < length)
	{
		dest[i] = src[i];
		i++;
	}
	// while (i < length)
	// {
	// 	dest[i] = '\0';
	// 	i++;
	// }
	return (dest);
}

static char	*offset_str_one_to_the_right(char **str)
{
	size_t	i;

	if (!**str)
		return (NULL);
	i = ft_strlen(*str);
	while (i > 1)
	{
		*str[i] = *str[i - 1];
		i--;
		*str += 1;
	}
	return (*str);
}

static char	*put_space_before_and_after_redir_operators(char *str)
{
	offset_str_one_to_the_right(&str);
	str[0] = ' ';
	while (*str)
	{
		if (skip_redirection_operator((const char **)&str))
			*str = ' ';
		else
			str++;
	}
	offset_str_one_to_the_right(&str);
	return (str);
}

static char *ft_realloc_plus_redir_count_times_two(char *str,
					short redir_count)
{
	char	*new_str;
	size_t	new_len;

	new_len = ft_strlen(str) + (redir_count * 2);
	new_str = ft_calloc(sizeof(char), new_len + 1);
	if (!new_str)
		return (NULL);
	new_str = ft_memmove(new_str, str, new_len);
	return (new_str);
}

static char	*space_out(char *str)
{
	short	redir_count;

	redir_count = count_redirection_operators(str);
	if (!redir_count)
		return (str);
	str = ft_realloc_plus_redir_count_times_two(str, redir_count);
	if (!str)
		return (NULL);
	while (is_redirection_operator((const char *)str))
		str = put_space_before_and_after_redir_operators(str);
	if (!str)
		return (NULL);
	write(1, "U\n", 2);
	return (str);
}
// =================================== SPACE_OUT ==============================