NAME			=	minishell

LIBFT_A			=	libft.a
LIBFT_DIR		=	libft/
LIBFT			=	$(addprefix $(LIBFT_DIR), $(LIBFT_A))

CC				=	gcc -g
INCLUDE			=	includes
CFLAGS			=	-Wall -Wextra -Werror -I$(INCLUDE)
RM				=	rm -f

SRCS = 		minishell.c \
			src/parser/parser.c \
			src/parser/tokenizer.c \
			src/parser/tokenizer_utils.c \
			src/parser/count.c \
			src/executor/exec_utils.c \
			src/executor/executor.c \
			src/executor/heredocument.c \
			src/executor/fork.c \
			src/executor/children.c \
			src/executor/filedescriptors.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			src/builtins/builtins.c \
			src/builtins/env.c \
			src/builtins/echo.c \
			src/builtins/error.c \
			src/builtins/export.c \
			src/builtins/pwd.c \
			src/builtins/cd.c \
			src/builtins/unset.c \
			src/builtins/exit.c \
			src/signals/signal.c \
			src/utils/matrixops.c \
			src/utils/matrixops2.c \
			src/utils/lstutils.c \
			src/utils/commandutils.c \
			src/utils/initialize.c

OBJS		=	$(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME): 	$(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft -L/Users/$(USER)/.brew/opt/readline/lib -lreadline -ltermcap
			@echo "\033[0;31m___  ____       _        _   _      _ _\033[0m"
			@echo "\033[0;31m|  \/  (_)     (_)      | | | |    | | |\033[0m"
			@echo "\033[0;31m| .  . |_ _ __  _ ______| |_| | ___| | |\033[0m"
			@echo "\033[0;31m| |\/| | | '_ \| |______|  _  |/ _ \ | |\033[0m"
			@echo "\033[0;31m| |  | | | | | | |      | | | |  __/ | |\033[0m"
			@echo "\033[0;31m\_|  |_/_|_| |_|_|      \_| |_/\___|_|_|\033[0m"
			@echo "                                        "
			@echo "                                        "
			@echo "\033[0;32mLinked into executable \033[0m\033[0;32mminishell\033[0m."


$(LIBFT):	
			@echo "Compiling libft.a"
			@$(MAKE) all -s -C $(LIBFT_DIR)

.c.o:
			@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

localclean:
			@$(RM) $(OBJS)
			@echo "Removed object files."

clean:		localclean
			@$(MAKE) clean -s -C $(LIBFT_DIR)
			@echo "Clean libft."

fclean:		localclean
			@$(MAKE) fclean -s -C $(LIBFT_DIR)
			@echo "Full clean libft."
			@$(RM) $(NAME)
			@echo "Removed executable."

re:			fclean all

.PHONY:		all clean fclean localclean re