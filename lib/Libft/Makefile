CC = cc
CFLAGS = -Wall -Wextra -Werror -I../../include
SRCS = $(filter-out $(BSRCS), $(shell ls *.c))
BSRCS = $(shell ls ft_lst*.c)
OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS:.c=.o)
LIBFT_H = ../../include/libft.h
NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

bonus: $(OBJS) $(BOBJS)
	ar rcs $(NAME) $?

%.o: %.c $(LIBFT_H)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re