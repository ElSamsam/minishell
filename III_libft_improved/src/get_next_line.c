/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:31:28 by saperrie          #+#    #+#             */
/*   Updated: 2024/01/20 03:41:10 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define FD_MAX_VAL 1025

char	*cat_and_clear_buf(char *line, char *buf)
{
	size_t	index;

	index = ft_find_chr(buf, '\n');
	if (index == 0)
		index = ft_find_chr(buf, '\0');
	line = ft_realloc(line, index);
	if (!line)
		return (NULL);
	line = ft_strncat(line, buf, index);
	return (line);
}

static char	*ft_gnl(int fd, char *buf, char *line, int read_ret_value)
{
	size_t		n_index;

	n_index = 0;
	while (true)
	{
		n_index = ft_find_chr(buf, '\n');
		if (n_index > 0)
			return (cat_and_clear_buf(line, buf));
		line = cat_and_clear_buf(line, buf);
		if (!line)
			return (NULL);
		read_ret_value = read(fd, buf, BUFFER_SIZE);
		if (read_ret_value < 0)
		{
			buf[0] = 0;
			free(line);
			return (NULL);
		}
		if (read_ret_value == 0)
			return (buf[0] = 0, line);
		buf[read_ret_value] = '\0';
	}
}

char	*get_next_line(int fd)
{
	static char	buf[FD_MAX_VAL][BUFFER_SIZE + 1];
	char		*line;
	int			read_ret_value;

	line = NULL;
	if (fd < 0 || fd >= FD_MAX_VAL)
		return (0);
	if (buf[fd][0])
	{
		line = cat_and_clear_buf(line, buf[fd]);
		if (!line)
			return (NULL);
		if (ft_find_chr(line, '\n'))
			return (line);
	}
	read_ret_value = read(fd, buf[fd], BUFFER_SIZE);
	if (read_ret_value < 0)
		return (buf[fd][0] = 0, free(line), NULL);
	if (read_ret_value == 0)
		return (buf[fd][0] = 0, line);
	buf[fd][read_ret_value] = '\0';
	return (ft_gnl(fd, buf[fd], line, read_ret_value));
}
