/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:21:44 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:09:20 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	isquote(char *token, int i, char target)
{
	if (*(token + i) != '\'' && *(token + i) != '\"' && *(token + i) != target)
		return (1);
	else
		return (0);
}

char	*four_dollar(char *token, t_envp *envport, char *dollar, size_t *i)
{
	size_t	sign;
	char	*four;
	char	*envp;
	size_t	j;

	sign = *i;
	while (token[++*i] && isdollar(token, *i) && isquote(token, *i, '?'))
		;
	four = ft_substr(token, sign + 1, *i - (sign + 1));
	envp = find_envport(token, envport, four, i);
	four = ft_calloc(ft_strlen(dollar) + ft_strlen(envp) + 1, sizeof(char));
	j = 0;
	dup2token(four, &j, dollar, 0);
	free(dollar);
	dup2token(four, &j, envp, 0);
	free(envp);
	return (four);
}

char	*for_quote(char *token, t_envp *envport, char *dollar, size_t *i)
{
	size_t	quote;

	quote = *i;
	while (*(token + ++*i) && *(token + *i) != '\"')
		;
	if (*(token + *i) == '\"')
	{
		*i = quote;
		dollar = four_quote(dollar, i, '\"');
		while (*(token + *i) != '\"' && *(token + *i))
		{
			if (*(token + *i) == '$')
			{
				dollar = four_dollar(token, envport, dollar, i);
				dollar = four_quote(dollar, i, *(token + *i));
				break ;
			}
			else if (*(token + *i) != '\"')
				dollar = just_do_it(token, dollar, i, '\"');
		}
		return (dollar);
	}
	*i = quote;
	dollar = just_quote(token, dollar, i);
	return (dollar);
}

char	*for_dollar(char *token, t_envp *envport)
{
	char	*dollar;
	size_t	i;
	size_t	j;

	dollar = (char *) ft_calloc(ft_strlen(token) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (*(token + i))
	{
		if (*(token + i) == '$')
			dollar = four_dollar(token, envport, dollar, &i);
		else if (*(token + i) == '\"')
			dollar = for_quote(token, envport, dollar, &i);
		else if (*(token + i) == '\'')
			dollar = single_quote(token, dollar, &i);
		else
			dollar = just_do_itq(token, dollar, &i);
	}
	free(token);
	return (dollar);
}

char	*single_quote(char *token, char *dollar, size_t *i)
{
	size_t	quote;

	quote = *i;
	while (*(token + ++*i) && *(token + *i) != '\'')
		;
	if (*(token + *i) == '\'')
	{
		*i = quote;
		dollar = four_quote(dollar, i, '\'');
		dollar = singular(token, dollar, i, '\'');
		dollar = four_quote(dollar, i, *(token + *i));
	}
	else
	{
		*i = quote;
		dollar = just_quote(token, dollar, i);
	}
	return (dollar);
}
