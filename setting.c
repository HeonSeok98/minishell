/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heolee <heolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:18:59 by heolee            #+#    #+#             */
/*   Updated: 2024/02/20 10:09:27 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setting2(int pipes[][2], pid_t *pid, int *num, int max_num)
{
	if (*pid != 0)
	{
		(*num)++;
		if (*num != max_num)
		{
			if (*num % 2 == 1)
				pipe(pipes[1]);
			else
				pipe(pipes[0]);
		}
		*pid = fork();
		if (*pid != 0)
		{
			if (*num % 2 == 1)
			{
				close(pipes[0][0]);
				close(pipes[0][1]);
			}
			else
			{
				close(pipes[1][0]);
				close(pipes[1][1]);
			}	
		}
	}
}

void	setting(int pipes[][2], pid_t *pid, int *num, int max_num)
{
	int		i;

	pipe(pipes[0]);
	if (max_num == 0)
	{
		close(pipes[0][0]);
		close(pipes[0][1]);
	}
	*num = 0;
	*pid = fork();
	i = 0;
	while (i != max_num)
	{
		setting2(pipes, pid, num, max_num);
		i++;
	}
	if (*pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
		signal(SIGINT, SIG_IGN);
}

void	link_pipe3(int pipe_index, int pipes[][2], int *num)
{
	if (pipe_index + 1 == *num)
	{
		if (pipe_index % 2 == 0)
		{
			dup2(pipes[0][0], STDIN_FILENO);
			close(pipes[0][0]);
			close(pipes[0][1]);
		}
		else if (pipe_index % 2 == 1)
		{
			dup2(pipes[1][0], STDIN_FILENO);
			close(pipes[1][0]);
			close(pipes[1][1]);
		}
	}
}

void	link_pipe2(int pipe_index, int pipes[][2], int *num)
{
	if (pipe_index == *num)
	{
		if (pipe_index % 2 == 0)
		{
			dup2(pipes[0][1], STDOUT_FILENO);
			close(pipes[0][0]);
			close(pipes[0][1]);
		}
		else if (pipe_index % 2 == 1)
		{
			dup2(pipes[1][1], STDOUT_FILENO);
			close(pipes[1][0]);
			close(pipes[1][1]);
		}
	}
}

void	link_pipe(t_node **node, int pipes[][2], int *num)
{
	int		pipe_index;
	t_node	*now;

	pipe_index = 0;
	now = *node;
	while (now)
	{
		if (now->type == PIPE)
		{
			link_pipe2(pipe_index, pipes, num);
			link_pipe3(pipe_index, pipes, num);
			pipe_index++;
		}
		now = now->next;
	}
}
