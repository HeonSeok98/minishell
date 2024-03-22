/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:25:32 by dna               #+#    #+#             */
/*   Updated: 2024/01/19 10:26:25 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		++len;
	return (len);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ptr;

	s1_len = gnl_strlen(s1);
	s2_len = gnl_strlen(s2);
	ptr = (char *) malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	else
	{
		while (*s1)
			*ptr++ = *s1++;
		while (*s2)
			*ptr++ = *s2++;
		*ptr = '\0';
		return (ptr - s1_len - s2_len);
	}
}

char	*gnl_lnjoin(char *buf, char *tmp)
{
	char	*tmp_ln;

	tmp_ln = gnl_strjoin(buf, tmp);
	free(buf);
	return (tmp_ln);
}

char	*gnl_strchr(const char *s, int c)
{
	char	char_c;

	char_c = (char) c;
	while (*s)
	{
		if (*s == char_c)
			return ((char *) s);
		else
			++s;
	}
	if (char_c == '\0')
		return ((char *) s);
	else
		return (NULL);
}

void	*gnl_calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned char	*ptr_b;
	unsigned char	uchar_c;
	size_t			len;

	ptr = (void *) malloc(count * size);
	if (!ptr)
		return (NULL);
	else
	{
		ptr_b = (unsigned char *) ptr;
		uchar_c = (unsigned char) 0;
		len = count * size;
		while (len--)
			*ptr_b++ = uchar_c;
		return (ptr);
	}
}
