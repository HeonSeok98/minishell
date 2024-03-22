CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFTDIR = ./libft
LIBFTNAME = libft.a
NAME = minishell
OBJS = $(SRCS:.c=.o)
RM = rm -f
SRCS = ./minishell.c			\
	   ./minishell_utils.c		\
	   ./tokenizer.c			\
	   ./builtin_cd.c			\
	   ./builtin_echo.c			\
	   ./builtin_env.c			\
	   ./builtin_exit.c			\
	   ./builtin_export.c		\
	   ./builtin_export_print.c	\
	   ./builtin_pwd.c			\
	   ./builtin_unset.c		\
	   ./environment.c			\
	   ./envp_utils.c			\
	   ./envp_utils2.c			\
	   ./execute.c				\
	   ./execute_utils.c		\
	   ./execute_utils2.c		\
	   ./find_path.c			\
	   ./handler.c				\
	   ./here_doc_write.c		\
	   ./lex_get.c				\
	   ./lex_get_from.c			\
	   ./lex_put.c				\
	   ./lex_put_to.c			\
	   ./lexer.c				\
	   ./lexer_utils.c			\
	   ./setting.c				\
	   ./syntax_error.c			\
	   ./redirections.c			\
	   ./parser.c				\
	   ./put_get.c				\
	   ./put_to_get_from.c		\
	   ./quotes.c				\
	   ./quotes_utils.c			\
	   ./utilities.c
	
%.o : %.c ./minishell.h
	$(CC) $(CFLAGS) -c $< -o $@ -I ./ -I ./libft

$(NAME) : $(OBJS) $(LIBFTDIR)/$(LIBFTNAME)
	$(CC) $(CFLAGS) -o $@ $^ -l readline -L ./libft -l ft

$(LIBFTDIR)/$(LIBFTNAME) : $(LIBFTDIR)
	make -C $(LIBFTDIR)

all : $(NAME)

clean :
	make -C $(LIBFTDIR) clean
	$(RM) $(OBJS)

fclean : clean
	make -C $(LIBFTDIR) fclean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
