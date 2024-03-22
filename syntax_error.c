/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:29:07 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:09:29 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(const char *s)
{
	write(2, "minishell: ", 11);
	write(2, s, ft_strlen(s));
}

void	access_error(t_node *node)
{
	if (access(node->data, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->data, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	else if (access(node->data, R_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->data, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(1);
	}
}

void	frexer(t_node *lst)
{
	t_node	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->data);
		free(tmp);
	}
}

char	*singular(char *token, char *dollar, size_t *i, char quote)
{
	size_t	sign;
	char	*just;
	char	*do_it;
	size_t	j;

	sign = *i;
	while (token[++*i] && token[*i] != quote)
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

char	*strdup2go(size_t *i)
{
	char	*target;

	target = ft_strdup("?");
	++*i;
	return (target);
}
