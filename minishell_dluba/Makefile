#NAMES
NAME		= minishell
MAKE		= make

#COMP
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

#SRC
SRC_DIR		= src
SRC			=	$(SRC_DIR)/dollar_parser.c \
				$(SRC_DIR)/duo_list_methods.c \
				$(SRC_DIR)/env_funcs.c   \
				$(SRC_DIR)/executor.c \
				$(SRC_DIR)/get_next_line.c \
				$(SRC_DIR)/get_next_line_utils.c \
				$(SRC_DIR)/initializing.c \
				$(SRC_DIR)/pipes.c  \
				$(SRC_DIR)/funcs_1.c  \
				$(SRC_DIR)/funcs_2.c  \
				$(SRC_DIR)/funcs_3.c  \
				$(SRC_DIR)/funcs_4.c  \
				$(SRC_DIR)/funcs_5.c  \
				$(SRC_DIR)/funcs_6.c  \
				$(SRC_DIR)/funcs_7.c  \
				$(SRC_DIR)/handler.c  \
				$(SRC_DIR)/heredoc.c  \
				$(SRC_DIR)/parser_1.c  \
				$(SRC_DIR)/parser_2.c  \
				$(SRC_DIR)/main.c  \
				$(SRC_DIR)/builtins/ft_cd.c  \
				$(SRC_DIR)/builtins/ft_echo.c  \
				$(SRC_DIR)/builtins/ft_env.c  \
				$(SRC_DIR)/builtins/ft_exit.c  \
				$(SRC_DIR)/builtins/ft_export.c  \
				$(SRC_DIR)/builtins/ft_pwd.c  \
				$(SRC_DIR)/builtins/ft_unset.c \


#INC
INC_DIR		= inc
INC			= $(INC_DIR) minishell.h

#OBJ
OBJ_DIR		= obj
OBJ			= $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRC:.c=.o))

#OBJ_INC
OBJ_INC		= -I $(INC_DIR)

#RMS
RM_DIR		= rm -rf
RM_FILE		= rm -f

#DEPS
$(NAME): $(OBJ)
	$(CC) $(OBJ) -lreadline -o $(NAME)

#OBJ DEPS
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(OBJ_INC) -c $< -o $@

$(OBJ)		:	| $(OBJ_DIR)
$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

#RULES
all:	$(NAME)

clean:
		${RM_DIR} ${OBJ_DIR}

fclean:	clean
		${RM_FILE} $(NAME)

re:		fclean all

#OTHER
.PHONY: all clean fclean re%
