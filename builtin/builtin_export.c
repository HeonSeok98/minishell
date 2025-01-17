/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:08:13 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:08:15 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_add3(t_envp **envport, char *cmd, t_envp	*now)
{
	t_envp	*now2;
	t_envp	*new;
	char	*new_env_name;
	char	*new_env_value;

	new_env_name = find_name(cmd);
	now2 = find_envp(envport, new_env_name);
	if (now2)
	{
		new_env_value = find_value(cmd);
		free(now2->value);
		now2->value = new_env_value;
		free(now->value);
		now->value = ft_strdup("0");
	}
	else
	{
		new = new_envp(cmd);
		envp_add_back(envport, new);
		free(now->value);
		now->value = ft_strdup("0");
	}
	free(new_env_name);
}

void	export_add2(t_envp **envport, char *cmd, t_envp	*now)
{
	t_envp	*new;

	if (cmd[0] == '=' || ft_isdigit(cmd[0]) || ft_strchr(cmd, '-'))
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		free(now->value);
		now->value = ft_strdup("1");
	}
	else if (ft_strchr(cmd, '='))
		export_add3(envport, cmd, now);
	else
	{
		if (!find_envp(envport, cmd))
		{
			new = extra_envp(cmd);
			envp_add_back(envport, new);
			free(now->value);
			now->value = ft_strdup("0");
		}
	}
}

void	export_add(t_node *node, t_envp **envport)
{
	int		i;
	char	**cmd_arr;
	t_envp	*now;

	now = find_envp(envport, "?");
	cmd_arr = ft_split(node->data, ' ');
	i = 1;
	while (cmd_arr[i])
	{
		export_add2(envport, cmd_arr[i], now);
		i++;
	}
	arr_free(cmd_arr);
}
