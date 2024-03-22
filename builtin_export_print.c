/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:53:05 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 17:53:09 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	re_envport(t_envp **envport)
{
	t_envp	*now;

	now = *envport;
	while (now)
	{
		now->printed = 0;
		now = now->next;
	}
}

void	print_export2(t_envp *min)
{
	if (ft_strcmp(min->name, "~") && ft_strcmp(min->name, "?"))
	{
		if (min->value)
			printf("declare -x %s=\"%s\"\n", min->name, min->value);
		else
			printf("declare -x %s\n", min->name);
	}
}

void	print_export(t_envp **envport)
{
	t_envp	*now1;
	t_envp	*now2;
	t_envp	*min;
	t_envp	*tmp;

	tmp = new_envp("~");
	now1 = *envport;
	while (now1)
	{
		min = tmp;
		now2 = *envport;
		while (now2)
		{
			if (ft_strcmp(min->name, now2->name) > 0 && now2->printed == 0)
				min = now2;
			now2 = now2->next;
		}
		print_export2(min);
		min->printed = 1;
		now1 = now1->next;
	}
	free(tmp);
	re_envport(envport);
}
