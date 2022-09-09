#NAMES
NAME		= minishell
MAKE		= make

#COMP
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

#SRC
SRC_DIR		= src
SRC			= $(SRC_DIR)/dollar_parser.c \
				$(SRC_DIR)/duo_list_methods.c \
				$(SRC_DIR)/env_funcs.c   \
				$(SRC_DIR)/executor.c \
				$(SRC_DIR)/get_next_line.c \
				$(SRC_DIR)/get_next_line_utils.c \
				$(SRC_DIR)/initializing.c \
				$(SRC_DIR)/itoa.c  \
				$(SRC_DIR)/lexer.c  \
				$(SRC_DIR)/parser.c  \
				$(SRC_DIR)/pipes.c  \
				$(SRC_DIR)/saver_parser.c  \
				$(SRC_DIR)/test.c  \
				$(SRC_DIR)/main.c  \
				$(SRC_DIR)/funcs.c  \
				$(SRC_DIR)/ft_split.c  \



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
