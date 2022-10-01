SRCS	= 			src/dollar_parser_1.c \
				src/dollar_parser_2.c \
				src/duo_list_methods_1.c \
				src/duo_list_methods_2.c \
				src/duo_list_methods_3.c \
				src/env_funcs_1.c   \
				src/env_funcs_2.c   \
				src/executor_2.c \
				src/executor_1.c \
				src/get_next_line/get_next_line.c \
				src/get_next_line/get_next_line_utils.c \
				src/initializing.c \
				src/pipes.c  \
				src/funcs_1.c  \
				src/funcs_2.c  \
				src/funcs_3.c  \
				src/funcs_4.c  \
				src/funcs_5.c  \
				src/funcs_6.c  \
				src/funcs_7.c  \
				src/handler.c  \
				src/files.c  \
				src/heredoc.c  \
				src/lexer_1.c   \
				src/lexer_2.c   \
				src/parser_1.c  \
				src/parser_2.c  \
				src/main.c  \
				src/ft_cd.c  \
				src/ft_echo.c  \
				src/ft_env.c  \
				src/ft_exit.c  \
				src/ft_export.c  \
				src/ft_pwd.c  \
				src/ft_unset.c \
		
OBJS		= ${SRCS:.c=.o}

NAME		= minishell

HEADER		= src/minishell.h

CC		= cc

CFLAGS		= -Wall -Wextra -Werror

INC		= -lreadline

.c.o:
	${CC} $(CFLAGS) -c $< -o ${<:.c=.o}

all: $(NAME) clean
	

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) ${INC} $(OBJS) -o $(NAME) 

clean:
	@rm -rf ${OBJS}

fclean:	clean
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re