/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:46:29 by dna               #+#    #+#             */
/*   Updated: 2024/02/22 11:46:31 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	redirecount(char *s, char *charset)
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
