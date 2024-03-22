/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:25:52 by dna               #+#    #+#             */
/*   Updated: 2024/01/19 10:23:35 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *buf, char *tmp)
{
	ssize_t	bytes;

	bytes = 1;
	while (buf && bytes > 0 && !gnl_strchr(buf, '\n'))
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes != -1)
		{
			*(tmp + bytes) = '\0';
			buf = gnl_lnjoin(buf, tmp);
			if (!buf)
			{
				free(tmp);
				return (NULL);
			}
		}
	}
	free(tmp);
	if (!*buf && !bytes)
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}

char	*read_next_line(int fd, char *buf)
{
	char	*tmp;

	if (!buf)
		return (NULL);
	tmp = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp)
	{
		free(buf);
		return (NULL);
	}
	buf = read_line(fd, buf, tmp);
	return (buf);
}

char	*get_new_line(char *buf)
{
	size_t	i;
	char	*line;

	if (*buf)
	{
		i = 0;
		while (*(buf + i) && *(buf + i) != '\n')
			++i;
		if (*(buf + i))
			line = gnl_calloc(i + 2, sizeof(char));
		else
			line = gnl_calloc(i + 1, sizeof(char));
		if (!line)
		{
			free(buf);
			return (NULL);
		}
		i = -1;
		while (*(buf + ++i) && *(buf + i) != '\n')
			*(line + i) = *(buf + i);
		if (*(buf + i))
			*(line + i) = '\n';
		return (line);
	}
	return (NULL);
}

char	*update(char *buf, char **line)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	j = 0;
	while (*(buf + i) && *(buf + i) != '\n')
		++i;
	if (*(buf + i))
	{
		tmp = gnl_calloc(gnl_strlen(buf) - i, sizeof(char));
		if (!tmp)
		{
			free(buf);
			free(*line);
			*line = NULL;
			return (NULL);
		}
		while (*(buf + ++i))
			*(tmp + j++) = *(buf + i);
		free(buf);
		return (tmp);
	}
	free(buf);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (read(fd, NULL, 0) > -1 && BUFFER_SIZE > 0)
	{
		if (!buf)
			buf = gnl_calloc(1, sizeof(char));
		buf = read_next_line(fd, buf);
		if (!buf)
			return (NULL);
		line = get_new_line(buf);
		if (!line)
		{
			buf = NULL;
			return (NULL);
		}
		buf = update(buf, &line);
		return (line);
	}
	if (buf)
	{
		free(buf);
		buf = NULL;
	}
	return (NULL);
}
