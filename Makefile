# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 15:54:09 by cmarouf           #+#    #+#              #
#    Updated: 2022/03/24 18:27:53 by anremiki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = main/main.c \
	  main/init_loop.c \
	  main/pipe_loop.c \
	  main/cmd_loop.c \
	  main/main_utils.c \
	  main/main_utils_2.c \
	  utils/sglt.c	\
	  utils/ft_putstr.c \
	  utils/error.c	\
	  utils/error_2.c	\
	  utils/ft_split.c \
	  utils/ft_split_path.c \
	  utils/ft_strjoin.c \
	  utils/ft_strjoinspace.c	\
	  utils/ft_strdup.c \
	  utils/ft_strcmp.c \
	  utils/ft_strstr.c \
	  utils/create_list.c \
	  utils/ft_lst_remove_if.c \
	  utils/ft_utils.c \
	  utils/utils_parsing.c \
	  utils/utils_parsing_2.c \
	  utils/free.c	\
	  utils/free_2.c	\
	  parsing/parse_dollar.c \
	  parsing/parse_redir.c \
	  parsing/check_redir.c \
	  parsing/check_pipe.c \
	  parsing/init_parsing.c \
	  parsing/check_quotes.c \
	  parsing/parsing.c \
	  parsing/parsing_utils.c \
	  parsing/parse_quotes.c \
	  parsing/sighandler.c	\
	  parsing/sighandler_2.c	\
	  parsing/pipe_handler.c	\
	  parsing/pipe_handler_utils.c	\
	  parsing/pipe_handler_2.c	\
	  parsing/pipe_handler_3.c	\
	  exec/heredoc.c	\
	  exec/get_child.c	\
	  exec/read_child.c	\
	  exec/attyin.c	\
	  exec/attyin_utils.c	\
	  exec/attyin_utils_2.c	\
	  exec/exec_cmd.c \
	  exec/redir.c \
	  exec/path.c	\
	  exec/heredoc_utils.c	\
	  built-in/cd.c \
	  built-in/upgrade.c \
	  built-in/pwd.c \
	  built-in/exit.c	\
	  built-in/exitdoc.c	\
	  built-in/exit_2.c	\
	  built-in/env.c \
	  built-in/export.c \
	  built-in/export_2.c \
	  built-in/unset.c \
	  built-in/echo.c	\
	  gnl/get_next_line.c	\
	  gnl/get_next_line_utils.c	\
	  prompt/prompt.c \
	  prompt/sadprompt.c \
	  prompt/check_prompt.c \
	  bonus/wildcard.c	\
	  bonus/wildcard_utils.c	\
	  bonus/wildcard_utils_2.c	\
	  bonus/wildcard_classic.c	\

OBJS = ${SRCS:.c=.o}

RM = rm -rf

CC = gcc

CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=1 

PRINT = 0

NAME = minishell

ifdef WITH_PRINT
	PRINT = 1
endif


.c.o:
	${CC} -I includes ${CFLAGS} -g3 -D PRINT=$(PRINT) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	make bonus -C ./libft
	$(CC) $(CFLAGS) -D PRINT=$(PRINT) -g3 $(OBJS) ./libft/libft.a -lreadline -o $(NAME)

debug: $(OBJS)
	make bonus -C ./libft
	$(CC) $(CFLAGS) -D PRINT=$(PRINT) -g3 $(OBJS) ./libft/libft.a -lreadline -o $(NAME)

p: fclean
	$(MAKE) WITH_PRINT=1

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SILENT: clean
