/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:26:54 by dna               #+#    #+#             */
/*   Updated: 2024/02/22 15:27:32 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	put_get(t_node **lst, char **token, size_t *flag, ssize_t k)
{
	size_t	size;
	int		type;

	if (**(token - 1) == (char) '<')
		type = READ;
	else
		type = WRITE;
	size = token_size(*token + k, " ", 0);
	if (ft_memcmp(*token + k, " ", 1))
	{
		if (!*flag)
		{
			if (type == READ)
				lex_put(lst, *token + k, size);
			else
				lex_get(lst, *token + k, size);
			*flag = 1;
		}
		else
			quotesize(lst, *token + k, size);
	}
	return (size);
}

void	lexeredirect(t_envp *envport, t_node **lst, char **token, ssize_t i)
{
	ssize_t	count;
	size_t	size;
	ssize_t	j;
	ssize_t	k;
	size_t	flag;

	j = 0;
	k = 0;
	flag = 0;
	count = redirecount(*(token + i + 1), " ");
	*(token + i + 1) = for_dollar(*(token + i + 1), envport);
	while (j < count)
	{
		size = put_get(lst, token + i + 1, &flag, k);
		k += size;
		++j;
	}
}
