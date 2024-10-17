NAME		:=	minishell

CFLAGS		:=	-Wextra -Wall -Werror -g
LDFLAGS		:=	-lreadline

HEADERS		:=	-Iinclude

LIBFT		:=	./lib/libft.a
LIBS		:=	$(LIBFT)

SRCS_DIR	:=	./src/
SRCS 		:=	minishell.c				\
				checker.c				\
				parsing.c				\
				dequoter.c				\
				expander.c				\
				redirections.c			\
				redirections_2.c		\
				freeing.c				\
				fork_and_processes.c	\
				struct.c				\
				util_env.c				\
				util_export.c			\
				util_path.c				\
				util_split.c			\
				util_strjoin.c			\
				util_others.c			\
				util_others2.c			\
				util_shlvl.c			\
				execution.c				\
				ft_echo.c				\
				ft_cd.c					\
				ft_pwd.c				\
				ft_export.c				\
				ft_unset.c				\
				ft_env.c				\
				ft_exit.c

SRCS		:=	$(addprefix $(SRCS_DIR), $(SRCS))

OBJS		:=	${SRCS:.c=.o}

all: $(NAME)

%.o: %.c
	@echo "Compiling $< to $@..."
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OBJS) $(LIBS)
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
