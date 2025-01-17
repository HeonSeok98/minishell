/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:07:48 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:07:51 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char *option)
{
	int	i;

	if (option[0] != '-')
		return (0);
	i = 1;
	while (option[i])
	{
		if (option[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	builtin_echo(t_node *node)
{
	char	**echo_arr;
	int		i;

	echo_arr = ft_split(node->data, ' ');
	if (check_n(echo_arr[1]))
	{
		i = 0;
		while (echo_arr[++i])
		{
			if (check_n(echo_arr[i]))
				continue ;
			if (!echo_arr[i + 1])
				printf("%s", echo_arr[i]);
			else
				printf("%s ", echo_arr[i]);
		}
	}
	else
		printf("%s\n", (node->data) + 7);
	arr_free(echo_arr);
}

void	syntax_error2(char *s, int option)
{
	if (option == 5)
		ft_putstr_fd("minishell: exit: ", 2);
	else
		ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	if (option == 1)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (option == 2)
		ft_putstr_fd(": is a directory\n", 2);
	else if (option == 3)
		ft_putstr_fd(": command not found\n", 2);
	else if (option == 4)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (option == 5)
		ft_putstr_fd(": numeric argument required\n", 2);
}
