# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/02 08:04:56 by zcadinot          #+#    #+#              #
#    Updated: 2026/01/05 13:28:13 by aeherve          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

SRC_DIR		= src
OBJ_DIR		= obj
INCLD_DIR	= includes
LIBFT_DIR	= library/libft

LIBFT			= $(LIBFT_DIR)/libft.a

SRCS		= main.c \
			src/core/shell_loop.c \
			src/core/start_shell.c \
			src/input/read_line.c \
			src/core/exec_cmd.c \
			src/core/status.c \
			src/core/exec_builtins.c \
			src/utils/header.c \
			src/core/cmd_utils.c \
			src/signals/signals.c \
			src/utils/frees.c \
			src/utils/envp.c

PARSING_FILES = src/parsing/parse_command.c \
				src/parsing/redirect_split.c \
				src/parsing/is_builtins.c \
				src/parsing/parsing_split.c \
				src/parsing/parse_error.c \
				src/parsing/extract_redirs.c

BUILTINS = src/builtins/env.c \
			src/builtins/echo.c \
			src/builtins/cd.c \
			src/builtins/exit.c \
			src/builtins/unset.c \
			src/builtins/export.c \
			src/builtins_pipe/echo_pipe.c \
			src/builtins_pipe/env_pipe.c \
			src/builtins_pipe/exec_builtin_pipe.c \
			src/builtins_pipe/pwd_pipe.c \
			src/builtins/pwd.c

LKL_FILES	= src/struct/init_struct.c \
			src/struct/var_list/ft_lklmodify_value.c \
			src/struct/var_list/ft_lkladd_front.c \
			src/struct/var_list/ft_lkladd_back.c \
			src/struct/var_list/ft_lklclear.c \
			src/struct/var_list/ft_lkllast.c \
			src/struct/var_list/ft_lkldel_one.c \
			src/struct/var_list/ft_lklremove.c \
			src/struct/var_list/ft_lklnew.c \
			src/struct/var_list/ft_lklsize.c

CMD_FILES	= src/struct/t_cmd/ft_cmdadd_front.c \
			src/struct/t_cmd/ft_cmdadd_back.c \
			src/struct/t_cmd/ft_cmdclear.c \
			src/struct/t_cmd/ft_cmdlast.c \
			src/struct/t_cmd/ft_cmddel_one.c \
			src/struct/t_cmd/ft_cmdnew.c \
			src/struct/t_cmd/build_argv.c \
			src/struct/t_cmd/extract_next_cmd.c \
			src/struct/t_cmd/ft_cmdsize.c

REDIR_FILES	= src/struct/t_redirs/ft_redirnew.c \
			src/struct/t_redirs/ft_redir_addback.c

OTHER_FILES	= src/utils/action.c \
			src/core/exec_pipeline.c

OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o) $(BUILTINS:%.c=$(OBJ_DIR)/%.o) $(LKL_FILES:%.c=$(OBJ_DIR)/%.o) \
			$(CMD_FILES:%.c=$(OBJ_DIR)/%.o) $(OTHER_FILES:%.c=$(OBJ_DIR)/%.o) $(PARSING_FILES:%.c=$(OBJ_DIR)/%.o) \
			$(REDIR_FILES:%.c=$(OBJ_DIR)/%.o)	

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -I. -I$(LIBFT_DIR)

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
