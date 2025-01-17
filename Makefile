CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFTDIR = ./libft
LIBFTNAME = libft.a
NAME = minishell
OBJS = $(SRCS:.c=.o)
RM = rm -f
SRCS = ./minishell.c			\
	   ./utils/minishell_utils.c		\
	   ./utils/tokenizer.c			\
	   ./builtin/builtin_cd.c			\
	   ./builtin/builtin_echo.c			\
	   ./builtin/builtin_env.c			\
	   ./builtin/builtin_exit.c			\
	   ./builtin/builtin_export.c		\
	   ./builtin/builtin_export_print.c	\
	   ./builtin/builtin_pwd.c			\
	   ./builtin/builtin_unset.c		\
	   ./envp/environment.c			\
	   ./envp/envp_utils.c			\
	   ./envp/envp_utils2.c			\
	   ./utils/execute.c				\
	   ./utils/execute_utils.c		\
	   ./utils/execute_utils2.c		\
	   ./utils/find_path.c			\
	   ./utils/handler.c				\
	   ./utils/here_doc_write.c		\
	   ./lexer/lex_get.c				\
	   ./lexer/lex_get_from.c			\
	   ./lexer/lex_put.c				\
	   ./lexer/lex_put_to.c			\
	   ./lexer/lexer.c				\
	   ./lexer/lexer_utils.c			\
	   ./utils/setting.c				\
	   ./utils/syntax_error.c			\
	   ./utils/redirections.c			\
	   ./utils/parser.c				\
	   ./utils/put_get.c				\
	   ./utils/put_to_get_from.c		\
	   ./utils/quotes.c				\
	   ./utils/quotes_utils.c			\
	   ./utils/utilities.c
	
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
