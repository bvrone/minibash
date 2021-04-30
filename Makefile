# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvrone <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/28 16:42:58 by bvrone            #+#    #+#              #
#    Updated: 2021/02/28 16:43:03 by bvrone           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
#CFLAGS =	-g
PARSER_DIR	= ./parser/
EXEC_DIR	= ./executor/
TERM_DIR	= ./termcup/
#ENGINE_DIR	= ./engine/
#GNL_DIR		= ./gnl/
#FT_LIST_DIR	= ./ft_list/
HEADERS		= ./headers/
LIB_DIR		= ./libft/
LIBNAME		= -lft
LIBTERM		= -ltermcap

SRC_MAIN	= main.c
SRC_PARSER	= $(addprefix $(PARSER_DIR), dollar_handler.c quotes_handler.c \
				skip_special_symbols.c symbol_matrix_utils2.c env_utils.c \
				pipeline_parser.c redirect_handler.c errors_handler.c \
				symbol_matrix_utils1.c syntax_checker.c syntax_checker2.c)
#SRC_GNL		= $(addprefix $(GNL_DIR), get_next_line.c get_next_line_utils.c)
#SRC_FT_LIST	= $(addprefix $(FT_LIST_DIR), ft_lstadd_back.c ft_lstadd_front.c \
#				ft_lstclear.c ft_lstdelone.c ft_lstfirst.c ft_lstiter.c \
#				ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c)
SRC_EXEC	= $(addprefix $(EXEC_DIR), ft_builtins.c ft_cd.c ft_echo.c \
				ft_env.c ft_executor.c ft_exit.c ft_export.c \
				ft_not_builtins.c ft_pwd.c ft_unset.c exec_pipe.c \
				utils_export.c)
SRC_TERM	= $(addprefix $(TERM_DIR), termcup.c utils_termcup.c hist.c)

OBJ_MAIN	= $(SRC_MAIN:.c=.o)
OBJ_PARSER	= $(SRC_PARSER:.c=.o)
#OBJ_GNL		= $(SRC_GNL:.c=.o)
#OBJ_FT_LIST	= $(SRC_FT_LIST:.c=.o)
OBJ_EXEC	= $(SRC_EXEC:.c=.o)
OBJ_TERM	= $(SRC_TERM:.c=.o)

#SRCS = $(SRC_MAIN) $(SRC_PARSER) $(SRC_ENGINE) $(SRC_GNL) $(SRC_FT_LIST)
SRCS = $(SRC_MAIN) $(SRC_PARSER) $(SRC_EXEC) $(SRC_TERM)

#OBJS = $(OBJ_MAIN) $(OBJ_PARSER) $(OBJ_ENGINE) $(OBJ_GNL) $(OBJ_FT_LIST)
OBJS = $(OBJ_MAIN) $(OBJ_PARSER) $(OBJ_EXEC) $(OBJ_TERM)

.PHONY:			all clean fclean re norm
#почитать про флаг -MMD (сейчас нет зависимостей от хедеров)
all:			$(LIBNAME) $(NAME)

$(LIBNAME):
				make -C $(LIB_DIR)

$(NAME): 		$(OBJS)
				$(CC) -L$(LIB_DIR) $(LIBNAME) $(LIBTERM) $(OBJS) -o $(NAME)

$(OBJ_PARSER): 	%.o: %.c $(HEADERS)
				$(CC) $(CFLAGS) -I$(HEADERS) -I$(LIB_DIR) -c $< -o $@

$(OBJ_EXEC): 	%.o: %.c $(HEADERS)
				$(CC) $(CFLAGS) -I$(HEADERS) -I$(LIB_DIR) -c $< -o $@

$(OBJ_TERM): 	%.o: %.c $(HEADERS)
				$(CC) $(CFLAGS) -I$(HEADERS) -I$(LIB_DIR) -c $< -o $@

$(OBJ_MAIN):	%.o: %.c $(HEADERS)
				$(CC) $(CFLAGS) -I$(HEADERS) -I$(LIB_DIR) -c $< -o $@

%.o:%.c%$(HEADERS)
	$(CC) $(CFLAGS) -o I$(HEADER) $@ -c $< 

clean:
				@rm -rf *.o
				@rm -f $(PARSER_DIR)/*.o
				@rm -f $(EXEC_DIR)/*.o
				@rm -f $(TERM_DIR)/*.o
				@make -C $(LIB_DIR) clean
				@echo Objects files deleted!

fclean:			clean
				rm -rf $(NAME)
				rm -rf $(LIB_DIR)libft.a

re:				fclean all

norm:
				norminette $(SRCS) $(HEADERS)
