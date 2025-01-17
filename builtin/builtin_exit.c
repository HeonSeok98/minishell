/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:08:05 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:08:08 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || '9' < str[i])
			return (1);
		i++;
	}
	if (i > 11)
		return (1);
	return (0);
}

void	builtin_exit_child(t_node *node, t_envp **envport)
{
	t_envp	*now;
	char	**exit_arr;

	exit_arr = ft_split(node->data, ' ');
	now = find_envp(envport, "?");
	if (!exit_arr[1])
		exit(ft_atoi(now->value));
	else
	{
		if (str_check(exit_arr[1]))
		{
			syntax_error2(exit_arr[1], 5);
			exit(255);
		}
		else if (exit_arr[2])
		{
			free(now->value);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			now->value = ft_strdup("1");
		}
		else
			exit(ft_atoi(exit_arr[1]));
	}
	arr_free(exit_arr);
}

void	builtin_exit(t_node *node, t_envp **envport)
{
	t_envp	*now;
	char	**exit_arr;

	ft_putstr_fd("exit\n", 1);
	exit_arr = ft_split(node->data, ' ');
	now = find_envp(envport, "?");
	if (!exit_arr[1])
		exit(ft_atoi(now->value));
	else
	{
		if (str_check(exit_arr[1]))
		{
			syntax_error2(exit_arr[1], 5);
			exit(255);
		}
		else if (exit_arr[2])
		{
			free(now->value);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			now->value = ft_strdup("1");
		}
		else
			exit(ft_atoi(exit_arr[1]));
	}
	arr_free(exit_arr);
}
