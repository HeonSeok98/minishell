/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:08:58 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:09:00 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_arr4(t_node *now, t_envp **envport)
{
	if (!ft_strcmp(now->data, "  env"))
		env(envport);
	else if (!ft_strncmp(now->data, "  env ", 6))
		syntax_error("env: too many arguments\n");
	else if (!ft_strcmp(now->data, "  pwd"))
		working_directory();
	else if (!ft_strncmp(now->data, "  pwd ", 6))
		working_directory();
	else if (!ft_strcmp(now->data, "  export"))
		print_export(envport);
	else if (!ft_strncmp(now->data, "  export ", 9))
		export_add(now, envport);
	else if (!ft_strncmp(now->data, "  unset ", 8))
		builtin_unset(now, envport);
	else if (!ft_strcmp(now->data, "  unset"))
		syntax_error("unset: not enough arguments\n");
	else
		return (0);
	return (1);
}

void	execute_arr5(t_node *now, t_envp **envport)
{
	if (!ft_strncmp(now->data, "  echo ", 7))
		builtin_echo(now);
	else if (!ft_strcmp(now->data, "  echo"))
		printf("\n");
	else if (!ft_strncmp(now->data, "  cd ", 5) \
		|| !ft_strcmp(now->data, "  cd"))
		change_directory(now->data, envport);
	else if (!ft_strncmp(now->data, "  exit ", 7) \
		|| !ft_strcmp(now->data, "  exit"))
		builtin_exit_child(now, envport);
	else
		execve_cmd(now, envport);
}

void	execute_arr3(t_node *now, int *num, int now_num, t_envp **envport)
{
	if (*num == now_num)
	{
		if (now->type == READ)
			red_read(now);
		else if (now->type == WRITE)
			red_write(now);
		else if (now->type == APPEND)
			red_append(now);
		else if (now->type == COMMAND)
		{
			if (!execute_arr4(now, envport))
				execute_arr5(now, envport);
		}
	}
}

void	execute_arr2(t_node **node, int *num, t_envp **envport)
{
	t_node	*now;
	int		now_num;

	now_num = 0;
	now = *node;
	while (now)
	{
		if (now->type == PIPE)
			now_num++;
		else
		{
			if (now->type >= HERE_DOC)
			{
				if (*num == now_num)
					red_here_doc(now->type - HERE_DOC);
			}
			execute_arr3(now, num, now_num, envport);
		}
		now = now->next;
	}
}

void	execute_arr(t_node **node, t_envp **envport, int max_num)
{
	pid_t	pid;
	int		pipes[2][2];
	int		num;

	if (!is_builtin(node, envport))
	{
		make_tmp(node, envport);
		setting(pipes, &pid, &num, max_num);
		if (pid == 0)
		{
			link_pipe(node, pipes, &num);
			execute_arr2(node, &num, envport);
			exit(0);
		}
		if (pid != 0)
			wait_chid_process(num + 1, envport, pid);
		unlink_tmp(node);
	}
}
