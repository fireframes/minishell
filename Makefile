NAME		:=	minishell

CFLAGS		:=	-Wextra -Wall -Werror
LDFLAGS		:=	-lreadline

HEADERS		:=	-Iinclude

# LIBFT		:=	./lib/libft.a
# LIBFTPRINTF	:=	./lib/libftprintf.a
#LIBS		:=	$(LIBFT) $(LIBFTPRINTF)

SRCS_DIR	:=	./src/
SRCS 		:=	minishell_tmp.c		\
				util_path.c			\
				util_split.c		\
				util_strjoin.c

SRCS		:=	$(addprefix $(SRCS_DIR), $(SRCS))

OBJS		:=	${SRCS:.c=.o}

all: $(NAME)

%.o: %.c
	@echo "Compiling $< to $@..."
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(LIBFT) $(LIBFTPRINTF) $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(LDFLAGS) -o $(NAME)
	@echo "Linking object files to create $(NAME)..."
	@echo "\n'$(NAME)' binary successfully created."

clean:
	@echo "Cleaning object files..."
	rm -rf $(OBJS)

fclean: clean
	@echo "\nPerforming full clean..."
	rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
