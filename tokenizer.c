/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:01:51 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:09:33 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*quotes(char **token, ssize_t i)
{
	unsigned char	*ptr_s;
	char			*quote;
	size_t			n;

	ptr_s = (unsigned char *) *(token + i);
	quote = "\'\"";
	n = ft_strlen(*(token + i));
	while (n--)
	{
		if (*ptr_s == quote[0] || *ptr_s == quote[1])
			return ((void *) ptr_s);
		else
			++ptr_s;
	}
	return (NULL);
}

size_t	token_count(char *s, char *charset)
{
	size_t	count;
	char	quotes;

	count = 0;
	while (*s)
	{
		if (ft_strchr(charset, *s))
			++count;
		else
		{
			if (*s == '\'' || *s == '\"')
			{
				quotes = *s;
				while (*++s && *s != quotes)
					;
				if (ft_strchr(charset, *(s + 1)))
					++count;
			}	
			else
				if (ft_strchr(charset, *(s + 1)) || *(s + 1) == '\0')
					++count;
		}
		++s;
	}
	return (count);
}

size_t	token_size(char *s, char *charset, size_t size)
{
	char	quotes;

	while (*s)
	{
		if (ft_strchr(charset, *s))
		{
			if (size)
				return (size);
			return (1);
		}
		if (*s == '\'' || *s == '\"')
		{
			quotes = *s;
			while (*++s && *s != quotes)
				++size;
			if (*s == quotes)
				size += 2;
			else
				size += 1;
		}
		else
			++size;
		++s;
	}
	return (size);
}

static char	**token_free(char **ptr, int i)
{
	if (!*(ptr + i))
	{
		while (i > -1)
		{
			free(*(ptr + i));
			--i;
		}
		ptr = NULL;
	}
	return (ptr);
}

char	**tokenizer(char *s)
{
	char	**token;
	size_t	count;
	size_t	i;
	size_t	size;

	count = token_count(s, "|&()<>");
	token = (char **) malloc((count + 1) * sizeof(char *));
	if (!token)
		return (NULL);
	i = 0;
	while (i < count)
	{
		size = token_size(s, "|&()<>", 0);
		*(token + i) = ft_substr(s, 0, size);
		if (!token_free(token, i))
			return (NULL);
		s += size;
		++i;
	}
	*(token + i) = NULL;
	return (token);
}
