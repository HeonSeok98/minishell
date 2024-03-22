/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_to_get_from.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:26:06 by dna               #+#    #+#             */
/*   Updated: 2024/02/22 15:26:45 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	put_to_get_from(t_node **lst, char **token, size_t *flag, ssize_t k)
{
	size_t	size;
	int		type;

	if (**(token - 1) == (char) '<')
		type = HERE_DOC;
	else
		type = APPEND;
	size = token_size(*token + k, " ", 0);
	if (ft_memcmp(*token + k, " ", 1))
	{
		if (!*flag)
		{
			if (type == HERE_DOC)
				lex_put_to(lst, *token + k, size);
			else
				lex_get_from(lst, *token + k, size);
			*flag = 1;
		}
		else
			quotesize(lst, *token + k, size);
	}
	return (size);
}

void	lexeredirects(t_envp *envport, t_node **lst, char **token, ssize_t i)
{
	ssize_t	count;
	size_t	size;
	ssize_t	j;
	ssize_t	k;
	size_t	flag;

	j = 0;
	k = 0;
	flag = 0;
	count = redirecount(*(token + i + 2), " ");
	if (*token[i] != '<')
		*(token + i + 2) = for_dollar(*(token + i + 2), envport);
	while (j < count)
	{
		size = put_to_get_from(lst, token + i + 2, &flag, k);
		k += size;
		++j;
	}
}
