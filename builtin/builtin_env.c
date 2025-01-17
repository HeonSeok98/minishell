/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:07:57 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:08:01 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_envp **envport)
{
	t_envp	*now;

	now = *envport;
	while (now)
	{
		if (ft_strcmp(now->name, "?") && now->value \
		&& ft_strcmp(now->value, ""))
			printf("%s=%s\n", now->name, now->value);
		now = now->next;
	}
}
