AR = ar
ARFLAGS = crs
BONUSSRCS = ./ft_lstnew.c	\
		./ft_lstadd_front.c	\
		./ft_lstsize.c		\
		./ft_lstlast.c		\
		./ft_lstadd_back.c	\
		./ft_lstdelone.c	\
		./ft_lstclear.c		\
		./ft_lstiter.c		\
		./ft_lstmap.c
BONUSOBJS = $(BONUSSRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
GNLSRCS = ./get_next_line/get_next_line.c		\
		  ./get_next_line/get_next_line_utils.c
NAME = libft.a
OBJS = $(SRCS:.c=.o) $(GNLSRCS:.c=.o)
RM = rm -f
SRCS = ./ft_isalpha.c	\
	   ./ft_isdigit.c	\
	   ./ft_isalnum.c	\
	   ./ft_isascii.c	\
	   ./ft_isprint.c	\
	   ./ft_strlen.c	\
	   ./ft_memset.c	\
	   ./ft_bzero.c		\
	   ./ft_memcpy.c	\
	   ./ft_memmove.c	\
	   ./ft_strlcpy.c	\
	   ./ft_strlcat.c	\
	   ./ft_toupper.c	\
	   ./ft_tolower.c	\
	   ./ft_strchr.c	\
	   ./ft_strrchr.c	\
	   ./ft_strncmp.c	\
	   ./ft_memchr.c	\
	   ./ft_memcmp.c	\
	   ./ft_strnstr.c	\
	   ./ft_atoi.c		\
	   ./ft_calloc.c	\
	   ./ft_strdup.c	\
	   ./ft_substr.c	\
	   ./ft_strjoin.c	\
	   ./ft_strtrim.c	\
	   ./ft_split.c		\
	   ./ft_itoa.c		\
	   ./ft_strmapi.c	\
	   ./ft_striteri.c	\
	   ./ft_putchar_fd.c\
	   ./ft_putstr_fd.c	\
	   ./ft_putendl_fd.c\
	   ./ft_putnbr_fd.c
TRUE = 1

ifdef BONUS
	TARGETOBJS = $(OBJS) $(BONUSOBJS)
else
	TARGETOBJS = $(OBJS)
endif

%.o : %.c ./libft.h ./get_next_line/get_next_line.h
	$(CC) -c $(CFLAGS) $< -o $@ -I ./ -I ./get_next_line

$(NAME) : $(TARGETOBJS)
	$(AR) $(ARFLAGS) $@ $^

all : $(NAME)

bonus :
	make BONUS=$(TRUE) all

clean :
	$(RM) $(OBJS) $(BONUSOBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
