/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:50:52 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:08:49 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*extra_envp(char *envp)
{
	t_envp	*new;

	new = (t_envp *) malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	else
	{
		new->name = ft_strdup(envp);
		new->value = NULL;
		new->printed = 0;
		new->next = NULL;
		new->prev = NULL;
		return (new);
	}
}
