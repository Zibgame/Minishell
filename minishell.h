/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:05:22 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/02 10:58:59 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "library/libft/libft.h"

typedef struct s_shell
{
	char	**env;
}	t_shell;

char	*read_line(void);
void	shell_loop(t_shell shell);
void	sig_handler(int sig);
void	init_signal(void);
void	start_shell(t_shell shell);
void	exec_cmd(t_shell shell, char *line);
t_shell	create_shell_struct(char **envp);
char	*get_cmd(char *cmd, char **env);

#endif
