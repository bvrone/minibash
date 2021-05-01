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
CFLAGS		=	-Wall -Wextra -Werror -g
PARSER_DIR	=	./parser/
EXEC_DIR	=	./executor/
TERM_DIR	=	./termcup/
HEADERS		=	./headers/
LIB_DIR		=	./libft/
LIBNAME		=	-lft
LIBTERM		=	-ltermcap

SRC_MAIN	= main.c utils_for_main.c
SRC_PARSER	= $(addprefix $(PARSER_DIR), dollar_handler.c quotes_handler.c \
				skip_special_symbols.c symbol_matrix_utils2.c env_utils.c \
				pipeline_parser.c redirect_handler.c errors_handler.c \
				symbol_matrix_utils1.c syntax_checker.c syntax_checker2.c)
SRC_HEADERS	= $(addprefix $(HEADERS), ft_executor.h minishell_structures.h \
				parser.h termcup.h)
SRC_EXEC	= $(addprefix $(EXEC_DIR), ft_builtins.c ft_cd.c ft_echo.c \
				ft_env.c ft_executor.c ft_exit.c ft_export.c \
				ft_not_builtins.c ft_pwd.c ft_unset.c exec_pipe.c \
				utils_export.c)
SRC_TERM	= $(addprefix $(TERM_DIR), termcup.c utils_termcup.c hist.c)

OBJ_MAIN	= $(SRC_MAIN:.c=.o)
OBJ_PARSER	= $(SRC_PARSER:.c=.o)
OBJ_EXEC	= $(SRC_EXEC:.c=.o)
OBJ_TERM	= $(SRC_TERM:.c=.o)

SRCS = $(SRC_MAIN) $(SRC_PARSER) $(SRC_EXEC) $(SRC_TERM)

OBJS = $(OBJ_MAIN) $(OBJ_PARSER) $(OBJ_EXEC) $(OBJ_TERM)

.PHONY:			all clean fclean re norm
#почитать про флаг -MMD (сейчас нет зависимостей от хедеров)
all:			$(LIBNAME) $(NAME)

$(LIBNAME):
				make -C $(LIB_DIR)

$(NAME): 		$(OBJS)
				$(CC) -L$(LIB_DIR) $(LIBNAME) $(LIBTERM) $(OBJS) -o $(NAME)

$(OBJ_PARSER): 	%.o: %.c $(SRC_HEADERS)
				$(CC) $(CFLAGS) -I$(HEADERS) -I$(LIB_DIR) -c $< -o $@

$(OBJ_EXEC): 	%.o: %.c $(SRC_HEADERS)
				$(CC) $(CFLAGS) -I$(HEADERS) -I$(LIB_DIR) -c $< -o $@

$(OBJ_TERM): 	%.o: %.c $(SRC_HEADERS)
				$(CC) $(CFLAGS) -I$(HEADERS) -I$(LIB_DIR) -c $< -o $@

$(OBJ_MAIN):	%.o: %.c $(SRC_HEADERS)
				$(CC) $(CFLAGS) -I$(HEADERS) -I$(LIB_DIR) -c $< -o $@

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
				norminette $(SRCS) $(HEADERS) $(LIB_DIR)
