/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:31:31 by dna               #+#    #+#             */
/*   Updated: 2024/02/23 13:31:39 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
		g_status = 1;
	}
}

void	default_handler(char *line)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	free(line);
}

void	here_doc_handler(int sig)
{
	if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		g_status = 2;
	}
}

int	signal_here_doc_handler(t_envp *envport)
{
	t_envp	*question;

	question = find_envp(&envport, "?");
	if (g_status == 2)
	{
		free(question->value);
		question->value = ft_strdup("257");
		return (1);
	}
	else
		return (0);
}

void	signal_handler(t_envp *envport)
{
	t_envp	*question;

	question = find_envp(&envport, "?");
	if (g_status == 1)
	{
		free(question->value);
		question->value = ft_strdup("1");
	}
}
