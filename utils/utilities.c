/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:47:26 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:09:37 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2token(char *s1, size_t *i, char *s2, size_t j)
{
	while (*(s2 + j))
		*(s1 + (*i)++) = *(s2 + j++);
}

char	*four_quote(char *dollar, size_t *i, char quote)
{
	char	*tmp;
	size_t	j;

	tmp = ft_calloc(ft_strlen(dollar) + 2, sizeof(char));
	j = 0;
	dup2token(tmp, &j, dollar, 0);
	free(dollar);
	*(tmp + j++) = quote;
	++*i;
	return (tmp);
}

char	*just_quote(char *token, char *dollar, size_t *i)
{
	size_t	tkl;
	char	*quote;
	size_t	j;

	tkl = ft_strlen(token + *i);
	quote = ft_calloc(ft_strlen(dollar) + tkl + 1, sizeof(char));
	j = 0;
	dup2token(quote, &j, dollar, 0);
	free(dollar);
	while (*(token + *i))
		*(quote + j++) = *(token + (*i)++);
	return (quote);
}

char	*just_do_itq(char *token, char *dollar, size_t *i)
{
	size_t	sign;
	char	*just;
	char	*do_it;
	size_t	j;

	sign = *i;
	while (token[++*i] && isquote(token, *i, '$'))
		;
	just = ft_substr(token, sign, *i - sign);
	do_it = ft_calloc(ft_strlen(dollar) + ft_strlen(just) + 1, sizeof(char));
	j = 0;
	dup2token(do_it, &j, dollar, 0);
	free(dollar);
	dup2token(do_it, &j, just, 0);
	free(just);
	return (do_it);
}

char	*just_do_it(char *token, char *dollar, size_t *i, char quote)
{
	size_t	sign;
	char	*just;
	char	*do_it;
	size_t	j;

	sign = *i;
	while (token[++*i] && (token[*i] != '$' && token[*i] != quote))
		;
	just = ft_substr(token, sign, *i - sign);
	do_it = ft_calloc(ft_strlen(dollar) + ft_strlen(just) + 1, sizeof(char));
	j = 0;
	dup2token(do_it, &j, dollar, 0);
	free(dollar);
	dup2token(do_it, &j, just, 0);
	free(just);
	return (do_it);
}
