/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:02:01 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:09:18 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	initialize_minishell(int argc, char *argv[])
{
	if (argc != 1)
	{
		write(2, "What The Shell: ", 16);
		++argv;
		while (*argv)
		{
			write(2, *argv, ft_strlen(*argv));
			write(2, ": ", 2);
			++argv;
		}
		write(2, "too many arguments\n", 19);
		exit(0);
	}
	else
	{
		rl_catch_signals = 0;
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	splitfree(char **ptr)
{
	size_t	i;

	i = 0;
	while (*(ptr + i))
		free(*(ptr + i++));
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	exit_handler(t_envp	*envport)
{
	envport_free(&envport);
	rl_clear_history();
	printf("\033[uexit\n");
	exit(0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_envp	*envport;
	char	**token;
	t_node	*lexical_token;

	initialize_minishell(argc, argv);
	envp_init(&envport, envp);
	while (1)
	{
		g_status = 0;
		line = readline("minishell$ \033[s");
		signal_handler(envport);
		if (line)
		{
			token = tokenizer(line);
			lexical_token = lexer(token, envport, 0);
			parser(&lexical_token, &envport);
			splitfree(token);
			add_history(line);
			default_handler(line);
		}
		else
			exit_handler(envport);
	}
	return (0);
}
