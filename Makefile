# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/02 08:04:56 by zcadinot          #+#    #+#              #
#    Updated: 2025/12/05 10:46:19 by aeherve          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

SRC_DIR     = src
OBJ_DIR     = obj
INCLD_DIR	= includes
LIBFT_DIR   = library/libft

LIBFT       = $(LIBFT_DIR)/libft.a

SRCS        = main.c \
              src/core/shell_loop.c \
              src/core/start_shell.c \
              src/input/read_line.c \
              src/core/exec_cmd.c \
              src/core/cmd_utils.c \
              src/struct/init_struct.c \
              src/signals/signals.c

OBJS        = $(SRCS:%.c=$(OBJ_DIR)/%.o)

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I. -I$(LIBFT_DIR)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
