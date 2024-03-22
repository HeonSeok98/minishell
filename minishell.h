/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:17:33 by dna               #+#    #+#             */
/*   Updated: 2024/02/14 16:17:34 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

# include "libft.h"

# define INIT 0
# define PIPE 1
# define READ 5
# define COMMAND 6
# define SUFFIX 7
# define WRITE 8
# define APPEND 9
# define HERE_DOC 10

int	g_status;

typedef struct s_envp
{
	char			*name;
	char			*value;
	int				printed;
	struct s_envp	*prev;
	struct s_envp	*next;
}	t_envp;

typedef struct s_node
{
	char			*data;
	int				type;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

void	handler(int sig);
void	default_handler(char *line);
void	here_doc_handler(int sig);
void	signal_handler(t_envp *envport);
int		signal_here_doc_handler(t_envp *envport);

void	*quotes(char **token, ssize_t i);
size_t	token_count(char *s, char *charset);
size_t	token_size(char *s, char *charset, size_t size);
char	**tokenizer(char *s);

t_node	*node_init(char *data, int type);
void	node_add_back(t_node **lst, t_node *node);

void	syntax_free(char *s, t_node *node);
ssize_t	lexer_command(t_envp *envport, t_node **lst, char **token, ssize_t i);
t_node	*lexer(char **token, t_envp *envport, ssize_t i);

ssize_t	lexer_pipe(t_node **lst, char **token, ssize_t i);
ssize_t	lexer_put(t_envp *envport, t_node **lst, char **token, ssize_t i);
ssize_t	lexer_put_to(t_envp *envport, t_node **lst, char **token, ssize_t i);
ssize_t	lexer_get(t_envp *envport, t_node **lst, char **token, ssize_t i);
ssize_t	lexer_get_from(t_envp *envport, t_node **lst, char **token, ssize_t i);

void	working_directory(void);
void	envp_init(t_envp **envport, char *envp[]);
t_envp	*new_envp(char *envp);
void	envp_add_back(t_envp **envport, t_envp *new);
void	envport_free(t_envp **envport);
char	**make_envp(t_envp **envport);
t_envp	*extra_envp(char *envp);

void	syntax_error(const char *s);
void	access_error(t_node *node);
void	frexer(t_node *lst);
char	*singular(char *token, char *dollar, size_t *i, char quote);
char	*strdup2go(size_t *i);

char	**parsing_path(t_envp **envport);
char	*make_path(char **path_arr, char *cmd);
void	red_read(t_node *node);
void	red_write(t_node *node);
void	red_here_doc(int hd_num);
void	red_append(t_node *node);
void	make_tmp(t_node **node, t_envp **envport);
void	execve_cmd(t_node *node, t_envp **envport);
void	here_doc_read(int hd_fd, char *end_sign, t_envp **envport, int fd);
void	here_doc_write(int here_doc_fd, char *line, t_envp **envport);
void	wait_chid_process(int num, t_envp **envport, pid_t pid);
void	setting(int pipes[][2], pid_t *pid, int *num, int max_num);
void	link_pipe(t_node **node, int pipes[][2], int *num);
void	execute_arr(t_node **node, t_envp **envport, int max_num);
void	link_pipe(t_node **node, int pipes[][2], int *num);
void	setting(int pipes[][2], pid_t *pid, int *num, int max_num);
void	node_free(t_node **lst);
char	**arr_free(char **arr);
void	parser(t_node **node, t_envp **envport);
void	unlink_tmp(t_node **node);
int		is_builtin(t_node **node, t_envp **envport);

int		ft_strcmp(char *s1, char *s2);
char	*find_envport(char *token, t_envp *envport, char *target, size_t *i);
char	*find_name(char *str);
char	*find_value(char *str);

void	builtin_exit(t_node *node, t_envp **envport);
void	builtin_exit_child(t_node *node, t_envp **envport);
void	env(t_envp **envport);
void	re_envport(t_envp **envport);
void	print_export2(t_envp *min);
void	print_export(t_envp **envport);
void	export_add(t_node *node, t_envp **envport);
void	builtin_unset(t_node *node, t_envp **envport);
void	change_directory(char *path, t_envp **envport);

size_t	isquote(char *token, int i, char target);
char	*four_dollar(char *token, t_envp *envport, char *dollar, size_t *i);
char	*for_quote(char *token, t_envp *envport, char *dollar, size_t *i);
char	*for_dollar(char *token, t_envp *envport);
char	*single_quote(char *token, char *dollar, size_t *i);

void	builtin_echo(t_node *node);

size_t	isdollar(char *token, int i);
void	cat_within(t_node **lst, char *token, size_t size, ssize_t cat);
void	cat_without(t_node **lst, char *token, size_t size, ssize_t cat);
void	quotesize(t_node **lst, char *token, size_t size);

void	lexeredirects(t_envp *envport, t_node **lst, char **token, ssize_t i);
void	lexeredirect(t_envp *envport, t_node **lst, char **token, ssize_t i);
size_t	redirecount(char *s, char *charset);

void	dup2token(char *s1, size_t *i, char *s2, size_t j);
char	*four_quote(char *dollar, size_t *i, char quote);
char	*just_quote(char *token, char *dollar, size_t *i);
char	*just_do_it(char *token, char *dollar, size_t *i, char quote);
char	*just_do_itq(char *token, char *dollar, size_t *i);

t_envp	*find_envp(t_envp **envport, char *name);
void	syntax_error2(char *s, int option);

void	lex_put(t_node **lst, char *token, size_t size);
void	lex_get(t_node **lst, char *token, size_t size);
void	lex_put_to(t_node **lst, char *token, size_t size);
void	lex_get_from(t_node **lst, char *token, size_t size);

#endif
